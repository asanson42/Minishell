/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mj <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 21:51:35 by mj                #+#    #+#             */
/*   Updated: 2022/04/28 22:29:01 by mj               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

extern int	g_exit_status;

char	*ft_find_value(char *cmd, char **env, t_list *envlist)
{
	char	*value;
	int		find;

	find = ft_env_exist(cmd, env, envlist);
	if (find == 1)
	{
		value = find_value_env(cmd, env);
		return (value);
	}
	else if (find == 2)
	{
		value = find_value_envlist(cmd, envlist);
		return (value);
	}
}

int	ft_find_envlist(char *cmd, t_list *envlist)
{
	int		i;
	t_env	*current;

	i = 0;
	while (cmd[i] == '\'' || cmd[i] == '\"')
		i++;
	while (envlist)
	{
		current = (t_env *)envlist->content;
		if (ft_strcmp(cmd, current->var) == 0)
			return (1);
		envlist = envlist->next;
	}
	return (0);
}

int	ft_env_exist(char *cmd, char **env, t_list *envlist)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	while (cmd[i] == '\'' || cmd[i] == '\"' || cmd[i] == '$')
		i++;
	while (ft_isalnum(cmd[i + j]))
		j++;
	while (env[k])
	{
		if (ft_strncmp(cmd + i, env[k], j) == 0)
			return (1);
		k++;
	}
	if (envlist != NULL)
	{
		if (ft_find_envlist(cmd, envlist))
			return (2);
		else
			return (0);
	}
	return (0);
}

int	ft_check_dollar_exp(char *cmd)
{
	int		i;

	if (cmd)
	{
		i = 0;
		while (cmd[i] == '\'' || cmd[i] == '\"')
			i++;
		if (cmd[i] == '$')
			return (1);
		else
			return (0);
	}
	return (0);
}
