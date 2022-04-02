/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanson <asanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 13:52:06 by asanson           #+#    #+#             */
/*   Updated: 2022/03/09 17:48:05 by mj               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	print_env(char **env, int fd)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_putstr_fd(env[i++], fd);
		ft_putchar_fd('\n', fd);
	}
}

void	ft_env(t_data *data, t_list *envx, int fd)
{
	t_env	*current;

	print_env(data->env, fd);
	while (envx)
	{
		current = (t_env *)envx->content;
		if (current->value != NULL)
		{
			ft_putstr_fd(current->var, fd);
			ft_putstr_fd(current->value, fd);
			ft_putchar_fd('\n', fd);
		}
		envx = envx->next;
	}
	return ;
}
