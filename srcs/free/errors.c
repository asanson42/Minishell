/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mj <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 16:06:10 by mj                #+#    #+#             */
/*   Updated: 2022/05/09 20:20:31 by mj               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

extern int	g_exit_status;

void	ft_maj_exit_status(t_list *envlist)
{
	t_env	*current;
	char	*new_value;

	while (envlist)
	{
		current = (t_env *)envlist->content;
		if (ft_strcmp(current->var, "$?") == 0)
		{
			new_value = ft_itoa(g_exit_status);
			free(current->value);
			current->value = new_value;
		}
		envlist = envlist->next;
	}
}

void	ft_error_command(char *cmd, char **path, t_data *data)
{
	if (path != NULL)
		ft_free_strs(path, ft_size_strs(path));
	data->succes = 0;
	ft_putstr_fd(cmd, 1);
	ft_putstr_fd(": command not found\n", 1);
	g_exit_status = 127;
	exit(g_exit_status);
}

void	error_exec(void)
{
	char	*error;

	error = strerror(errno);
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}

void	error_pid(void)
{
	char	*error;

	error = strerror(errno);
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
}
