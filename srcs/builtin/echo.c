/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanson <asanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 13:43:15 by asanson           #+#    #+#             */
/*   Updated: 2022/05/09 20:26:34 by mj               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

extern int	g_exit_status;

static int	printf_backslash(int size, int fd)
{
	if (size == 1)
	{
		ft_putchar_fd('\n', fd);
		return (1);
	}
	else
		return (0);
}

static void	printf_backslash2(int n, int fd)
{
	if (n == 0)
		ft_putchar_fd('\n', fd);
}

static	void	printf_space(char **cmds, int i, int fd)
{
	int	size_cmds;

	size_cmds = ft_size_strs(cmds);
	if (i < size_cmds - 1)
		ft_putchar_fd(' ', fd);
}

void	change_succes(t_data *data)
{
	if ((!(data->succes == 1)) && g_exit_status != 0)
		data->succes = 1;
	else
		data->succes = 0;
}

void	ft_echo(char **cmds, int fd, t_data *data)
{
	int	size;
	int	n;
	int	i;

	n = 0;
	size = ft_size_strs(cmds);
	if (printf_backslash(size, fd) == 1)
		return ;
	if (ft_strcmp(cmds[1], "-n") == 0)
		n = 1;
	if (size == 2 && n == 1)
		return ;
	if (n == 1)
		i = 2;
	else
		i = 1;
	while (cmds[i])
	{
		ft_putstr_fd(cmds[i], fd);
		printf_space(cmds, i, fd);
		i++;
	}
	printf_backslash2(n, fd);
	return (change_succes(data));
}
