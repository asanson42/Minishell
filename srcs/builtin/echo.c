/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanson <asanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 13:43:15 by asanson           #+#    #+#             */
/*   Updated: 2022/02/27 13:43:19 by asanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	ft_echo(char *cmd, int n, int fd)
{
	int	i;
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
	}
}
