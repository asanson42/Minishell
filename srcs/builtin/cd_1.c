/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanson <asanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 13:51:45 by asanson           #+#    #+#             */
/*   Updated: 2022/02/27 17:35:51 by asanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

ssize_t	find_env(char *arg, char **env)
{
	char	*sub;
	ssize_t	i;
	ssize_t	index;

	if (!arg)
		return (-1);
	i = 0;
	while (env[i])
	{
		index = get_char_by_index(env[i], '=');
		if (index == -1)
			index = ft_strlen(env[i]);
		sub = ft_substr(env[i], 0, index);
		if (sub)
		{
			if (ft_strequ(sub, arg))
			{
				free(sub);
				return (i);
			}
			free(sub);
		}
		i++;
	}
	return (-1);
}

size_t	get_envs_count(char **envp)
{
	size_t	count;

	count = 0;
	while (envp[count])
		count++;
	return (count);
}

char	*get_env(char *arg, char **env)
{
	ssize_t	i;
	ssize_t	len;

	if (!arg)
		return (NULL);
	len = ft_strlen(arg);
	i = find_env(arg, env);
	if (i != -1)
		return (ft_substr(env[i], (len + 1), ft_strlen(env[i])));
	return (NULL);
}
