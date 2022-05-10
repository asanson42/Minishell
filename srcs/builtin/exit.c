/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mj <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 21:48:20 by mj                #+#    #+#             */
/*   Updated: 2022/05/05 21:48:40 by mj               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

extern int	g_exit_status;

int	ft_digit_cmd(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (!(cmd[i] >= '0' || cmd[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

void	ft_exit(char **cmds, t_data *data)
{
	int	size_cmds;

	size_cmds = ft_size_strs(cmds);
	if (size_cmds >= 3)
	{
		if (ft_digit_cmd(cmds[1]) == 0)
		{
			g_exit_status = ft_atoi(cmds[1]);
			ft_putstr_fd("bash: too many args\n", data->stdfd[1]);
		}
		else
			ft_putstr_fd("bash: Illegal number\n", data->stdfd[1]);
		return ;
	}
	else if (size_cmds == 2)
	{
		g_exit_status = ft_atoi(cmds[1]);
		return ;
	}
	ft_clean_all(data);
}
