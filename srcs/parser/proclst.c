/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proclst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mj <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 20:34:32 by mj                #+#    #+#             */
/*   Updated: 2022/04/30 17:19:58 by mj               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	add_process(t_process *process, t_list **proclst)
{
	t_list	*new;

	new = ft_dlstnew(process);
	if (new == NULL)
		return (1);
	ft_dlstadd_back(proclst, new);
	return (0);
}

int	ft_proclst(t_list *tokenlst, t_list **proclst, t_data *data)
{
	t_process	*process;

	while (tokenlst)
	{
		process = malloc(sizeof(*process));
		if (process == NULL)
			return (1);
		ft_bzero(process, sizeof(*process));
		if (ft_rdirlst(tokenlst, &process->rdirlst, process))
			return (1);
		if (ft_cmds(&tokenlst, &process->cmds, data, process->rdirlst))
			return (1);
		if (tokenlst && ((t_token *)tokenlst->content)->tokentype == 5)
			tokenlst = tokenlst->next;
		if (add_process(process, proclst))
			return (1);
	}
	return (0);
}
