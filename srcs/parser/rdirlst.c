/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdirlst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mj <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 20:29:00 by mj                #+#    #+#             */
/*   Updated: 2022/04/28 20:31:28 by mj               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_rdir	*ft_trdir(t_token *current, t_token *next, t_process *process)
{
	t_rdir	*rdir;

	rdir = malloc(sizeof(*rdir));
	if (rdir == NULL)
		return (NULL);
	if (current->tokentype == 1)
		rdir->type = IN;
	else if (current->tokentype == 2)
		rdir->type = OUT;
	else if (current->tokentype == 3)
		rdir->type = HEREDOC;
	else if (current->tokentype == 4)
		rdir->type = A_OUT;
	rdir->name = ft_strdup(next->tokenstr);
	if (rdir->name == NULL)
	{
		free(rdir);
		return (NULL);
	}
	return (rdir);
}

static int	free_r(t_rdir *rdir)
{
	free(rdir);
	return (1);
}

int	ft_rdirlst(t_list *tokenlst, t_list **rdirlst, t_process *process)
{
	t_token	*current;
	t_rdir	*rdir;
	t_list	*new;	

	while (tokenlst)
	{
		current = (t_token *)tokenlst->content;
		if (current->tokentype == 5)
			break ;
		if (current->tokentype >= 1 \
			&& current->tokentype <= 4 && tokenlst->next)
		{	
			rdir = ft_trdir(current, tokenlst->next->content, process);
			if (rdir == NULL)
				return (1);
			new = ft_dlstnew(rdir);
			if (new == NULL)
				return (free_r(rdir));
			ft_dlstadd_back(rdirlst, new);
		}
		tokenlst = tokenlst->next;
	}
	return (0);
}
