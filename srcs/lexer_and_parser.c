/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_and_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mj <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 15:53:00 by mj                #+#    #+#             */
/*   Updated: 2022/05/05 23:13:08 by mj               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

extern int	g_exit_status;

void	lexer_and_parser(t_data *data)
{
	t_list	*lst;
	t_token	*current;

	find_token(data->cmdline, &data->tokenlst, &data->lexer);
	lst = data->tokenlst;
	while (lst)
	{
		current = (t_token *)lst->content;
		lst = lst->next;
	}
	ft_expand(data->tokenlst, data);
	if (data->tokenlst)
	{
		if (ft_check_tokens(data->tokenlst))
		{
			printf("bash: Syntax Error\n");
			g_exit_status = 2;
			free_data(data);
		}
		if (ft_proclst(data->tokenlst, &data->proclst, data))
			free_data(data);
		run_cmds(data);
	}
}
