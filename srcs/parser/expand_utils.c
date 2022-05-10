/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mj <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 15:24:44 by mj                #+#    #+#             */
/*   Updated: 2022/04/30 15:25:55 by mj               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	free_c(t_token *current)
{
	free(current->tokenstr);
	current->tokenstr = NULL;
	current = NULL;
}

void	ft_empty_value(char *cmd, t_token *current, t_list *tokenlst)
{
	int		d_quotes;
	int		s_quotes;
	int		check_first;
	int		ret;

	s_quotes = ft_check_simple(cmd);
	d_quotes = ft_check_double(cmd);
	check_first = 0;
	ret = 0;
	if (s_quotes == 0 && d_quotes == 0)
		ret = 1;
	else if (s_quotes == 2 && d_quotes == 0)
		ret = 0;
	else if (s_quotes == 0 && d_quotes == 2)
		ret = 1;
	else if (s_quotes == 2 || d_quotes == 2)
		check_first = ft_check_first(cmd);
	if (check_first == 2)
		ret = 1;
	else if (check_first == 1)
		ret = 0;
	if (ret == 1)
		free_c(current);
}
