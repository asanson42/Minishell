/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_built.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanson <asanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 13:52:47 by asanson           #+#    #+#             */
/*   Updated: 2022/02/27 17:42:12 by asanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	run_built(char *cmd, char **cmds, t_data *data)
{
	if (ft_strcmp(cmd, "cd") == 0)
		ft_cd(cmds, data);
	/*else if (ft_strcmp(cmd, "echo") == 0)
		//ft_echo();
	else if (ft_strcmp(cmd, "env") == 0)
		//ft_env();
	else if (ft_strcmp(cmd, "export") == 0)
		//ft_export();
	else if (ft_strcmp(cmd, "pwd") == 0)
		//ft_pwd();
	else if (ft_strcmp(cmd, "unset") == 0)
		//ft_unset();*/
	else if (ft_strcmp(cmd, "exit") == 0)
		ft_clean_all(data);
	else
		return ;
}
