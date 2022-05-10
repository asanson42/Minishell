/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mj <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 22:54:37 by mj                #+#    #+#             */
/*   Updated: 2022/05/09 20:23:29 by mj               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

extern int	g_exit_status;

void	ft_end_value(t_token *current, char *value, char *cmd)
{
	int		double_quotes;
	int		simple_quotes;
	int		check_first;

	if (value == NULL)
		return ;
	simple_quotes = ft_check_simple(current->tokenstr);
	double_quotes = ft_check_double(current->tokenstr);
	if (simple_quotes == 2 && double_quotes == 2)
		check_first = ft_check_first(current->tokenstr);
	if (simple_quotes == 0 && double_quotes == 0)
		ft_replace_value(current, value);
	else if (simple_quotes == 2 && double_quotes == 0)
		return ;
	else if (simple_quotes == 0 && double_quotes == 2)
		ft_replace_value(current, value);
	else if (simple_quotes == 2 && double_quotes == 2 && check_first == 1)
		ft_replace_simple(current, value, cmd);
	else if (simple_quotes == 2 && double_quotes == 2 && check_first == 2)
		ft_replace_double(current, value, cmd);
}

void	ft_exit_status(t_token *current, t_data *data)
{
	char	*value;

	if (data->succes == 1 && g_exit_status != 0)
		g_exit_status = 0;
	value = ft_itoa(g_exit_status);
	free(current->tokenstr);
	current->tokenstr = value;
}

void	ft_expand_utils(t_token *current, t_list *tokenlst, t_data *data)
{
	char	*value;

	if (ft_env_exist(current->tokenstr, data->env, data->envlist))
	{
		value = ft_find_value(current->tokenstr, data->env, data->envlist);
		return (ft_end_value(current, value, current->tokenstr));
	}
	if (ft_strcmp("export", ((t_token *) \
	tokenlst->previous->content)->tokenstr) == 0)
		return ;
	return (ft_empty_value(current->tokenstr, current, tokenlst));
}

void	ft_expand(t_list *tokenlst, t_data *data)
{
	t_token	*current;
	char	*value;

	while (tokenlst)
	{
		current = (t_token *)tokenlst->content;
		if (current->tokentype == 3)
			return ;
		if (current->tokentype == 0)
		{
			if (ft_strcmp(current->tokenstr, "$?") == 0)
				ft_exit_status(current, data);
			if (ft_check_dollar_exp(current->tokenstr))
				return (ft_expand_utils(current, tokenlst, data));
		}
		tokenlst = tokenlst->next;
	}
	return ;
}
