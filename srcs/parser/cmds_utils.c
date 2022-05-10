/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mj <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 00:53:05 by mj                #+#    #+#             */
/*   Updated: 2022/04/29 00:53:40 by mj               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	compare_value(char *tmp, char *str)
{
	int		i;

	i = 0;
	while (str[i] != '=')
		i++;
	i++;
	if (strcmp(str + i, tmp) == 0)
		return (1);
	return (0);
}

int	find_env_value(char *tmp, char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (compare_value(tmp, env[i]))
			return (1);
		i++;
	}
	return (0);
}

int	find_value_envlst(char *tmp, t_list *envlist)
{
	t_env	*current;

	while (envlist)
	{
		current = (t_env *)envlist->content;
		if (ft_strcmp(tmp, current->value) == 0)
			return (1);
		envlist = envlist->next;
	}
	return (0);
}

int	ft_value_found(char *tokenstr, t_data *data)
{
	char	*tmp;
	int		quotes;
	int		i;
	int		ret;

	quotes = 0;
	i = 0;
	tmp = NULL;
	ret = 0;
	while (tokenstr[i])
	{
		if (tokenstr[i] == '\'' || tokenstr[i] == '\"')
			quotes++;
		i++;
	}
	tmp = ft_substr(tokenstr, (quotes / 2), (i - quotes));
	if (find_value_envlst(tmp, data->envlist))
		ret = 1;
	else if (find_env_value(tmp, data->env))
		ret = 1;
	free(tmp);
	return (ret);
}
