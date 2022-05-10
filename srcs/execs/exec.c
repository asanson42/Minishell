/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mj <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 15:30:13 by mj                #+#    #+#             */
/*   Updated: 2022/05/09 19:47:56 by mj               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

extern int	g_exit_status;

int	find_access(char *cmd, char *path)
{
	char	*f_access;

	f_access = is_access(cmd, path);
	if (f_access == NULL)
		return (-1);
	if (access(f_access, X_OK) == 0)
	{
		free(f_access);
		return (1);
	}
	free(f_access);
	return (0);
}

char	*find_path_utils(char *cmd, char *split_path, char **split_paths)
{
	char	*path_access;

	path_access = is_access(cmd, split_path);
	ft_free_strs(split_paths, ft_size_strs(split_paths));
	return (path_access);
}

void	ft_check_ret(int ret, char *cmd, char **split_path, t_data *data)
{
	if (ret == 0)
		ft_error_command(cmd, split_path, data);
}

char	*find_path(char *cmd, t_data *data)
{
	char	**path;
	char	**split_path;
	char	*path_acces;
	int		i;
	int		ret;

	i = 0;
	if (cmd && (cmd[0] == '.' || cmd[0] == '/'))
		return (cmd);
	while (i < ft_size_strs(data->env) \
	&& (ft_strncmp(data->env[i], "PATH=", 5) != 0))
		i++;
	split_path = ft_strsplit(data->env[i], ':');
	if (split_path == NULL)
		ft_error_command(cmd, NULL, data);
	i = 0;
	while (split_path[i] && (cmd[0] != '\0'))
	{
		ret = find_access(cmd, split_path[i]);
		if (ret == 1)
			return (find_path_utils(cmd, split_path[i], split_path));
		i++;
	}
	ft_check_ret(ret, cmd, split_path, data);
	return (cmd);
}

void	ft_exec(t_data *data, t_process *process)
{
	pid_t	pid;
	char	*pathname;
	int		i;

	i = 0;
	pid = fork();
	if (pid == 0)
	{
		pathname = find_path(process->cmds[i], data);
		if (execve(pathname, process->cmds, data->env))
			error_exec();
	}
	if (pid < 0)
		error_pid();
	else
	{
		signal(SIGINT, sig_int2);
		signal(SIGQUIT, SIG_IGN);
		wait_pid(pid);
		signal(SIGINT, sig_int);
		signal(SIGQUIT, SIG_IGN);
	}
}
