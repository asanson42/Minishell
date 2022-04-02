/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanson <asanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 13:43:15 by asanson           #+#    #+#             */
/*   Updated: 2022/03/09 18:02:55 by mj               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	ft_echo(char **cmds, int fd)
{
	/*int	i;
	int	len;

	i = 0;
	len = ft_strlen(cmd);
	while (i < len - 1)
		ft_putchar_fd(cmd[i++], fd);
	if (cmd[i] != '\n')
	{
		ft_putchar_fd(cmd[i], fd);
		if (n == 1)
			ft_putchar_fd('%', fd);
	}
	else
	{
		if (n != 1)
			ft_putchar_fd(cmd[i], fd);
	}*/
	int size = 0;
	int n = 0;
	int i = 0;

	size = ft_size_strs(cmds);
	if (size == 1)
	{
		ft_putchar_fd('\n', fd);
		return ;
	}
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
		i++;
	}
	if (n == 0)
		ft_putchar_fd('\n', fd);
	return ;
}
