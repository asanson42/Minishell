/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mj <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 16:01:05 by mj                #+#    #+#             */
/*   Updated: 2022/04/30 18:32:16 by mj               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

extern int	g_exit_status;

void	ft_free_strs(char **strs, int index)
{
	int	i;

	i = 0;
	if (strs != NULL)
	{
		while (i < index)
		{
			free(strs[i]);
			i++;
		}
		free(strs);
		strs = NULL;
	}
}

void	free_rdir(t_list **rdirlst)
{
	t_rdir	*rdir;
	t_list	*tmp;

	while (*rdirlst)
	{
		tmp = (*rdirlst)->next;
		rdir = (*rdirlst)->content;
		if (rdir->name)
			free(rdir->name);
		free(rdir);
		free(*rdirlst);
		(*rdirlst) = tmp;
	}
}

void	free_process(t_list **proclst)
{
	t_process	*process;
	t_list		*tmp;

	while (*proclst)
	{
		tmp = (*proclst)->next;
		process = (*proclst)->content;
		if (process->cmds)
			ft_free_strs(process->cmds, ft_size_strs(process->cmds));
		if (ft_dlstsize(process->rdirlst) >= 1)
			free_rdir(&process->rdirlst);
		free(process);
		free(*proclst);
		(*proclst) = tmp;
	}
}

int	ft_in_envlist(char *tokenstr, t_list *envlist)
{
	t_env	*current;

	if (envlist != NULL)
	{
		while (envlist)
		{
			current = (t_env *)envlist->content;
			if (ft_strcmp(tokenstr, current->var) == 0)
				return (1);
			if (ft_strcmp(tokenstr, current->value) == 0)
				return (1);
			envlist = envlist->next;
		}
	}
	return (0);
}

void	free_token(t_list **tokenlst, t_list *envlist)
{
	t_token	*token;
	t_list	*tmp;

	while (*tokenlst)
	{
		tmp = (*tokenlst)->next;
		token = (*tokenlst)->content;
		if (token->tokenstr && ft_in_envlist(token->tokenstr, envlist) == 0)
			free(token->tokenstr);
		else if (ft_strcmp(token->tokenstr, " ") == 0)
			free(token->tokenstr);
		free(token);
		free((*tokenlst));
		(*tokenlst) = tmp;
	}
}
