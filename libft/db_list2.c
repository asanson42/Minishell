/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_list2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanson <asanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 16:26:34 by asanson           #+#    #+#             */
/*   Updated: 2022/02/27 16:26:35 by asanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstdelone(t_list *dlst, void (*del)(void *))
{
	if (dlst != NULL)
	{
		if (del && dlst->content)
			(del)(dlst->content);
		free(dlst);
		dlst = NULL;
	}
}

void	ft_dlstclear(t_list **dlst, void (*del)(void *))
{
	t_list		*current;
	t_list		*next;

	if (*dlst)
	{
		current = *dlst;
		while (current != NULL)
		{
			next = current->next;
			ft_dlstdelone(current, (del));
			current = next;
		}
		*dlst = NULL;
	}
}
