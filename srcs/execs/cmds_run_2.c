/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_run_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mj <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 18:23:10 by mj                #+#    #+#             */
/*   Updated: 2022/05/09 20:13:54 by mj               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

extern int	g_exit_status;

char	*ft_find_var(char *line, t_data *data)
{
	char	*new_line;

	if (ft_check_dollar(line))
	{
		if (ft_env_exist(line, data->env, data->envlist))
			new_line = get_value(line, data->env, data->envlist);
		else
			new_line = get_empty(line);
		return (new_line);
	}
	else
		return (line);
}

void	here_doc(t_data *data, t_rdir *rdir)
{
	int		mode;
	char	*line;

	mode = 1;
	while (mode)
	{
		data->pipefd[1] = open(rdir->name, O_RDWR | O_APPEND | O_CREAT, 0664);
		line = readline("> ");
		if (ft_strcmp(line, rdir->name) == 0 && ft_strcmp(line, " ") != 0)
		{
			mode = 0;
			free(line);
			break ;
		}
		line = ft_find_var(line, data);
		ft_putendl_fd(line, data->pipefd[1]);
	}
	unlink(rdir->name);
}

void	ft_dup2_in(t_data *data, t_rdir *rdir)
{
	if (rdir->type == 0)
	{
		data->pipefd[1] = open(rdir->name, O_RDONLY, 0);
		if (data->pipefd[1] < 0)
		{
			printf("error_file: %s\n", rdir->name);
			g_exit_status = 1;
			exit(1);
		}
	}
	else if (rdir->type == 2)
		here_doc(data, rdir);
	dup2(data->pipefd[1], data->stdfd[0]);
	close(data->pipefd[1]);
}

void	ft_dup2_out(t_data *data, t_rdir *rdir)
{
	if (rdir->type == 1)
	{
		data->pipefd[0] = open(rdir->name, O_CREAT | O_RDWR | O_TRUNC, 0664);
		if (data->pipefd[0] < 3)
		{
			perror(rdir->name);
			exit(1);
		}
		dup2(data->pipefd[0], data->stdfd[1]);
		close(data->pipefd[0]);
	}
	else if (rdir->type == 3)
	{
		data->pipefd[0] = open(rdir->name, O_CREAT | O_RDWR | O_APPEND, 0664);
		if (data->pipefd[0] < 3)
		{
			perror(rdir->name);
			exit(1);
		}
		dup2(data->pipefd[0], data->stdfd[1]);
		close(data->pipefd[0]);
	}
}
