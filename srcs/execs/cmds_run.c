/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_run.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanson <asanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 01:41:03 by asanson           #+#    #+#             */
/*   Updated: 2022/05/09 20:12:14 by mj               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

extern int	g_exit_status;

void	ft_fork(t_data *data, t_process *process)
{
	t_rdir	*rdir;
	int		i;
	char	*pathname;

	i = 0;
	while (process->rdirlst)
	{
		rdir = (t_rdir *)process->rdirlst->content;
		if (rdir->type == 0 || rdir->type == 2)
			ft_dup2_in(data, rdir);
		else if (rdir->type == 1 || rdir->type == 3)
			ft_dup2_out(data, rdir);
		process->rdirlst = process->rdirlst->next;
	}
	if (is_builtins(process->cmds[i]))
	{
		run_built(process->cmds[i], process->cmds, data);
		exit(0);
	}
	else
	{
		pathname = find_path(process->cmds[i], data);
		if (execve(pathname, process->cmds, data->env))
			error_exec();
	}
}

void	ft_pipe_redir(t_data *data, t_process *process)
{
	pid_t	pid;
	int		status;

	if (pipe(data->pipefd) == -1)
		error_pid();
	pid = fork();
	if (pid < 0)
	{
		exit(1);
	}
	else if (pid == 0)
	{
		ft_fork(data, process);
	}
	else
	{
		close(data->pipefd[0]);
		close(data->pipefd[1]);
		signal(SIGINT, sig_int2);
		signal(SIGQUIT, SIG_IGN);
		wait_pid(pid);
		signal(SIGINT, sig_int);
		signal(SIGQUIT, SIG_DFL);
	}
}

int	size_proclst(t_list *lst)
{
	int		i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

void	run_cmds(t_data *data)
{
	t_process	*process;
	t_rdir		*rdir;
	int			i;
	int			size;
	t_list		*lst;

	size = ft_dlstsize(data->proclst);
	process = NULL;
	if (size > 1)
		ft_run_multi(data, data->proclst, size);
	else
	{
		lst = data->proclst;
		while (lst)
		{	
			process = (t_process *)lst->content;
			if (process->rdirlst)
				ft_pipe_redir(data, process);
			else if (is_builtins(process->cmds[0]))
				run_built(process->cmds[0], process->cmds, data);
			else
				ft_exec(data, process);
			lst = lst->next;
		}
	}
}
