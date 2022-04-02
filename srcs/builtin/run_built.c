/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_built.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanson <asanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 13:52:47 by asanson           #+#    #+#             */
/*   Updated: 2022/03/28 14:21:20 by mj               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	run_built(char *cmd, char **cmds, t_data *data)
{
	if (ft_strcmp(cmd, "cd") == 0)
		ft_cd(cmds, data);
	else if (ft_strcmp(cmd, "echo") == 0)
		ft_echo(cmds, data->stdfd[1]);
	else if (ft_strcmp(cmd, "env") == 0)
		ft_env(data, data->envlist, data->stdfd[1]);
	else if (ft_strcmp(cmd, "export") == 0)
		ft_export(cmds[1], &data->envlist, data, data->stdfd[1]);
	else if (ft_strcmp(cmd, "pwd") == 0)
		ft_pwd(data->env, data->stdfd[1]);
	else if (ft_strcmp(cmd, "unset") == 0)
		ft_unset(cmds[1], &data->envlist, data);
	else if (ft_strcmp(cmd, "exit") == 0)
		ft_clean_all(data);
	else
		return ;
}
