/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanson <asanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 16:26:48 by asanson           #+#    #+#             */
/*   Updated: 2022/02/27 16:26:49 by asanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_dlstsize(t_list *dlst)
{
	int	size;

	size = 0;
	while (dlst)
	{
		size++;
		dlst = dlst->next;
	}
	return (size);
}

t_list	*ft_dlstnew(void *content)
{
	t_list	*dnew;

	dnew = (t_list *)malloc(sizeof(t_list));
	if (!dnew)
		return (NULL);
	dnew->content = content;
	dnew->previous = NULL;
	dnew->next = NULL;
	return (dnew);
}

t_list	*ft_dlstlast(t_list *dlst)
{
	t_list	*dtmp;

	if (!dlst)
		return (NULL);
	dtmp = dlst;
	while (dtmp->next)
		dtmp = dtmp->next;
	return (dtmp);
}

void	ft_dlstadd_back(t_list **adlst, t_list *dnew)
{
	t_list	*dlast;

	if (!dnew || !adlst)
		return ;
	if (!*adlst)
	{
		*adlst = dnew;
		return ;
	}
	dlast = ft_dlstlast(*adlst);
	dnew->previous = dlast;
	dnew->next = NULL;
	dlast->next = dnew;
}

void	ft_dlstadd_front(t_list **adlst, t_list *dnew)
{
	if (!dnew)
		return ;
	if (!*adlst)
	{
		*adlst = dnew;
		(*adlst)->previous = NULL;
		(*adlst)->next = NULL;
	}
	else
	{
		dnew->previous = NULL;
		dnew->next = *adlst;
		(*adlst)->previous = dnew;
		*adlst = dnew;
	}
}
