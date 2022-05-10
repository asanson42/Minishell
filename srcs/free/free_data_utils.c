/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mj <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 16:09:57 by mj                #+#    #+#             */
/*   Updated: 2022/04/12 16:09:58 by mj               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

extern int	g_exit_status;

void	free_envlist(t_list **envlist)
{
	t_env	*env;
	t_list	*tmp;

	while (*envlist)
	{
		tmp = (*envlist)->next;
		env = (*envlist)->content;
		if (env->var)
			free(env->var);
		if (env->value)
			free(env->value);
		free(env);
		free((*envlist));
		(*envlist) = tmp;
	}
}

void	free_data(t_data *data)
{
	if (ft_dlstsize(data->proclst) >= 1)
	{
		free_process(&data->proclst);
		free(data->proclst);
		data->proclst = NULL;
	}
	if (data->tokenlst)
	{
		free_token(&data->tokenlst, data->envlist);
		free(data->tokenlst);
		data->tokenlst = NULL;
	}
}
