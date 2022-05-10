/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mj <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 15:59:59 by mj                #+#    #+#             */
/*   Updated: 2022/05/05 21:53:44 by mj               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

extern int	g_exit_status;

void	free_end_mode(char *line, t_data *data)
{
	if (line)
		free(line);
	free_data(data);
}

int	ft_end(char *line, t_data *data, int mode)
{
	if (mode == 0)
	{
		printf("Déconnexion\n");
		if (line)
			free(line);
	}
	if (data->prompt != NULL)
	{
		free(data->prompt);
		data->prompt = NULL;
	}
	if (data->env != NULL)
		ft_free_strs(data->env, ft_size_strs(data->env));
	if (data->envlist != NULL)
	{
		free_envlist(&data->envlist);
		free(data->envlist);
	}
	rl_clear_history();
	return (1);
}

void	ft_clean_all(t_data *data)
{
	printf("Déconnexion\n");
	ft_end(data->cmdline, data, 1);
	exit(0);
}
