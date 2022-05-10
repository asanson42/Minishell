/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mj <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 21:15:44 by mj                #+#    #+#             */
/*   Updated: 2022/05/10 17:54:23 by mmahias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	check_end(char *str)
{
	int		len;
	int		i;

	len = ft_strlen(str);
	i = len - 1;
	if (str[i] == '|')
		return (1);
	return (0);
}

int	check_word(char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		j = i + 1;
		if (str[i] == '<')
			if (str[j] == '>')
				return (1);
		if (str[i] == '>')
			if (str[j] == '<')
				return (1);
		if (str[i] == '|')
			if (str[j] == '|')
				return (1);
		i++;
	}
	if (check_end(str) == 1)
		return (1);
	return (0);
}

int	check_quotes_close(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len > 1 && check_close(str, '\'') != -1)
	{
		if (check_close(str + check_close(str, '\'') + 1, '\'') == -1)
			return (1);
	}
	else if (len > 1 && check_close(str, '\"') != -1)
	{
		if (check_close(str + check_close(str, '\"') + 1, '\"') == -1)
			return (1);
	}
	else if (len <= 1 && str[0] == '\'' || str[0] == '\"')
		return (1);
	else if (!(str[0] == '\'' || str[0] == '\"'))
	{
		if (check_close(str, '\'') != -1)
			return (1);
		if (check_close(str, '\"') != -1)
			return (1);
	}
	return (0);
}

int	ft_check_syntax(t_list *lst, t_token *current)
{
	if (current->tokentype == 5 && (lst->next == NULL \
				|| ((t_token *)lst->next->content)->tokentype == 5))
		return (1);
	if ((current->tokentype >= 1 && current->tokentype <= 4))
		if (lst->next == NULL \
				|| ((t_token *)lst->next->content)->tokentype != 0)
			return (1);
	if (current->tokentype == 0)
		if (check_word(current->tokenstr) != 0)
			return (1);
	if (check_quotes_close(current->tokenstr))
		return (1);
	return (0);
}

int	ft_check_tokens(t_list *lst)
{
	t_token	*current;
	t_token	*first;

	first = lst->content;
	if (first->tokentype == 5 || (first->tokentype != 0 && lst->next == NULL))
		return (1);
	while (lst)
	{
		if (((t_token *)lst->content)->tokenstr)
		{
			current = lst->content;
			if (ft_check_syntax(lst, current) == 1)
				return (1);
		}
		lst = lst->next;
	}
	if (current->tokentype >= 1 && current->tokentype <= 5)
		return (1);
	return (0);
}
