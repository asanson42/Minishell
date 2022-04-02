/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanson <asanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 13:52:38 by asanson           #+#    #+#             */
/*   Updated: 2022/03/09 17:46:30 by mj               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	ft_print_pwd(char *pwd, int fd)
{
	int	i;

	i = 4;
	while (pwd[i])
		ft_putchar_fd(pwd[i++], fd);
}

void	ft_pwd(char **env, int fd)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PWD=", 3) == 0)
		{
			ft_print_pwd(env[i], fd);
			return ;
		}
		i++;
	}
	return ;
}
