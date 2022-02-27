/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanson <asanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 13:51:51 by asanson           #+#    #+#             */
/*   Updated: 2022/02/27 17:38:34 by asanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	*add_home_path(char *path, char **envp)
{
	char	*tmp;
	char	*tmpp;

	if (!ft_strncmp(path, "~/", 2))
	{
		tmp = get_env("HOME", envp);
		if (tmp)
		{
			tmpp = ft_substr(path, 1, ft_strlen(path));
			free(path);
			path = ft_strjoin(tmp, tmpp);
			free(tmp);
			free(tmpp);
			return (path);
		}
	}
	return (path);
}

char	**realloc_envs(size_t size, char **envp)
{
	char	**new;
	size_t	i;

	new = (char **)malloc(sizeof(char *) * (size + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (envp[i] && i < size)
	{
		new[i] = ft_strdup(envp[i]);
		i++;
	}
	new[size] = 0;
	ft_free_array(envp);
	return (new);
}

int	modify(char *new_env, char **envp, size_t len, ssize_t i)
{
	char	*tmp;
	char	*new;

	tmp = ft_substr(envp[i], 0, (len + 1));
	if (!tmp)
		return (0);
	new = ft_strjoin(tmp, new_env);
	if (!new)
		return (0);
	if (envp[i] != NULL)
		free(envp[i]);
	free(tmp);
	envp[i] = new;
	return (1);
}
