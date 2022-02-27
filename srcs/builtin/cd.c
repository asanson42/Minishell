/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanson <asanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 13:43:44 by asanson           #+#    #+#             */
/*   Updated: 2022/02/27 17:44:06 by asanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	set_env(char *env, char **envp, char *new_env)
{
	char	*tmp;
	ssize_t	i;
	size_t	len;

	if (!env || !new_env)
		return (0);
	len = ft_strlen(env);
	i = -1;
	i = find_env(env, envp);
	if (i != -1)
		return (modify(new_env, envp, len, i));
	else
	{
		len = get_envs_count(envp) + 1;
		envp = realloc_envs(len, envp);
		tmp = ft_strjoin(env, "=");
		envp[len - 1] = ft_strjoin(tmp, new_env);
		free(tmp);
		return (1);
	}
	return (0);
}

static int	change(char *path, char **env, int home)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!chdir(path))
	{
		if (pwd)
		{
			set_env("OLDPWD", env, pwd);
			free(pwd);
		}
		pwd = getcwd(NULL, 0);
		if (pwd)
		{
			set_env("PWD", env, pwd);
			free(pwd);
		}
		if (home)
			free(path);
		return (1);
	}
	free(pwd);
	return (0);
}

static int	set_directory(char *path, char **env, int home)
{
	struct stat	st;

	if (change(path, env, home))
		return (1);
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(path, 2);
	if (stat(path, &st) == -1)
		ft_putstr_fd(": No such file or directory", 2);
	else if (!(st.st_mode & S_IXUSR))
		ft_putstr_fd(": Permission denied", 2);
	else
		ft_putstr_fd(": Not a directory", 2);
	ft_putchar_fd('\n', 2);
	if (home)
		free(path);
	return (1);
}

static int	s_path(char **args, char **envp)
{
	char	*tmp;

	if (ft_strequ(args[1], "-"))
	{
		tmp = get_env("OLDPWD", envp);
		if (tmp)
		{
			set_directory(tmp, envp, 0);
			free(tmp);
		}
		tmp = get_env("PWD", envp);
		if (tmp)
		{
			ft_putstr_fd(tmp, 1);
			free(tmp);
			ft_putchar_fd('\n', 1);
		}
		return (1);
	}
	return (set_directory(args[1], envp, 0));
}

int	ft_cd(char **args, t_data *data)
{
	char	*home;

	home = NULL;
	if (args && args[1] && args[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	if (!args[1] || ft_strequ(args[1], "~") || ft_strequ(args[1], "--"))
	{
		home = get_env("HOME", data->env);
		if (!home)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (1);
		}
		return (set_directory(home, data->env, 1));
	}
	args[1] = add_home_path(args[1], data->env);
	return (s_path(args, data->env));
}
