/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mj <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 21:38:14 by mj                #+#    #+#             */
/*   Updated: 2022/04/30 15:01:25 by mj               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

extern int	g_exit_status;

char	*ft_split_value(char *env, char *cmd, int size)
{
	int		len;
	int		i;
	char	*value;

	len = 0;
	i = 0;
	while (env[size] != '=')
		size++;
	len = ft_strlen(env + (size + 1));
	value = malloc(sizeof(char) * (len + 1));
	if (!value)
		return (NULL);
	size++;
	while (env[(size + i)])
	{
		value[i] = env[(size + i)];
		i++;
	}
	value[i] = '\0';
	return (value);
}

char	*free_s(char *split)
{
	free(split);
	return (NULL);
}

char	*find_value_env(char *cmd, char **env)
{
	char	*split;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	split = NULL;
	while (cmd[i] == '\'' || cmd[i] == '\"' || cmd[i] == '$')
		i++;
	while (ft_isalnum(cmd[i + j]))
		j++;
	while (env[k])
	{
		if (ft_strncmp(cmd + i, env[k], j) == 0)
		{
			split = ft_split_value(env[k], cmd + i, j);
			if (!split)
				return (free_s(split));
			return (split);
		}
		k++;
	}
	return (free_s(split));
}

char	*value_envlist(char *value)
{
	char	*new;
	int		i;
	int		j;

	if (value == NULL)
		return (NULL);
	new = malloc(sizeof(char) * ft_strlen(value));
	if (!new)
		return (NULL);
	j = 0;
	if (value[0] == '=')
		i = 1;
	while (value[i])
		new[j++] = value[i++];
	new[j] = '\0';
	return (new);
}

char	*find_value_envlist(char *cmd, t_list *envlist)
{
	t_env	*current;
	char	*value;
	int		i;

	i = 0;
	while (cmd[i] == '\'' || cmd[i] == '\"')
		i++;
	while (envlist)
	{
		current = (t_env *)envlist->content;
		if (ft_strcmp(cmd + i, current->var) == 0)
		{
			value = value_envlist(current->value);
			return (value);
		}
		envlist = envlist->next;
	}
	return (NULL);
}
