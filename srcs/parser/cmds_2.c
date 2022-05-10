/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mj <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 20:18:09 by mj                #+#    #+#             */
/*   Updated: 2022/04/30 17:55:24 by mj               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	size_cmds(t_list *tokenlst)
{
	int		size;
	t_token	*current;

	size = 0;
	while (tokenlst)
	{
		if (((t_token *)tokenlst->content)->tokenstr)
		{
			current = (t_token *)tokenlst->content;
			if (current->tokentype == 0)
			{
				if (tokenlst->previous == NULL)
					size++;
				else if (tokenlst->previous != NULL)
					if (((t_token *)tokenlst->previous->content)->tokentype < 1 \
					|| ((t_token *)tokenlst->previous->content)->tokentype > 4)
						size++;
			}
			if (current->tokentype == 5)
				break ;
		}
		tokenlst = tokenlst->next;
	}
	return (size);
}

int	ft_tab_cmds(t_list **tokenlst, char **cmds, t_data *data, t_list *rdirlst)
{
	t_token	*current;
	int		i;

	i = 0;
	while (*tokenlst)
	{
		current = (*tokenlst)->content;
		if (current->tokentype == 5)
			break ;
		else if (current->tokentype == 0 && current->tokenstr != NULL)
		{
			if ((*tokenlst)->previous == NULL)
				cmds[i] = new_cmd(current->tokenstr, data);
			else if ((*tokenlst)->previous != NULL)
			{
				if (((t_token *)(*tokenlst)->previous->content)->tokentype < 1 \
				|| ((t_token *)(*tokenlst)->previous->content)->tokentype > 4)
					cmds[i] = new_cmd(current->tokenstr, data);
			}
			if (cmds[i] != NULL)
				i++;
		}
		*tokenlst = (*tokenlst)->next;
	}
	return (0);
}

int	ft_cmds(t_list **tokenlst, char ***cmds, t_data *data, t_list *rdirlst)
{
	int		size;
	char	**new_cmds;

	size = size_cmds(*tokenlst);
	new_cmds = NULL;
	new_cmds = malloc(sizeof(char *) * (size + 1));
	new_cmds = ft_memset(new_cmds, 0, sizeof(char *));
	if (new_cmds == NULL)
		return (1);
	new_cmds[size] = NULL;
	if (ft_tab_cmds(tokenlst, new_cmds, data, rdirlst) > 0)
		return (1);
	*cmds = new_cmds;
	return (0);
}
