/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mj <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 18:28:13 by mj                #+#    #+#             */
/*   Updated: 2022/05/09 19:17:30 by mj               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

extern int	g_exit_status;

int	wait_pid2(int status)
{
	int		sig;

	if (WIFEXITED(status))
		if (g_exit_status != 2)
			g_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == 2)
		{
			if (g_exit_status != 2)
				g_exit_status = 130;
			else if (sig == 3)
			{
				if (g_exit_status != 2)
				{
					g_exit_status = 131;
					write (1, "Quit (core dumped)\n", 19);
				}
			}
		}
	}
}

void	close_all(t_data *data)
{
	close(data->stdinfd);
	close(data->pipefd[0]);
	close(data->pipefd[1]);
}

void	ft_fork2(t_data *data, t_process *process, int cnt, int next_lst)
{
	t_rdir	*rdir;
	char	*pathname;

	if (next_lst >= 1)
		dup2(data->pipefd[1], STDOUT_FILENO);
	if (cnt != 0)
		dup2(data->stdinfd, STDIN_FILENO);
	close_all(data);
	while (process->rdirlst)
	{
		rdir = (t_rdir *)process->rdirlst->content;
		if (rdir->type == 0 || rdir->type == 2)
			ft_dup2_in(data, rdir);
		else if (rdir->type == 1 || rdir->type == 3)
			ft_dup2_out(data, rdir);
		process->rdirlst = process->rdirlst->next;
	}
	if (is_builtins(process->cmds[0]))
	{
		run_built(process->cmds[0], process->cmds, data);
		exit(0);
	}
	pathname = find_path(process->cmds[0], data);
	if (execve(pathname, process->cmds, data->env))
		error_exec();
}

void	ft_pipe_multi(t_data *data, t_process *process, int cnt, int next_lst)
{
	pid_t	pid;

	if (pipe(data->pipefd) == -1)
	{
		error_pid();
	}
	signal(SIGINT, sig_int2);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid < 0)
	{
		exit(1);
	}
	else if (pid == 0)
	{
		signal(SIGINT, sig_int);
		signal(SIGQUIT, SIG_DFL);
		ft_fork2(data, process, cnt, next_lst);
	}
	else
	{
		dup2(data->pipefd[0], data->stdinfd);
		close(data->pipefd[0]);
		close(data->pipefd[1]);
	}
}

void	ft_run_multi(t_data *data, t_list *proclst, int size)
{
	int			status;
	t_process	*process;
	int			i;

	i = 0;
	data->stdinfd = dup(STDIN_FILENO);
	while (i < size && proclst)
	{
		process = (t_process *)proclst->content;
		if (proclst->next != NULL)
			ft_pipe_multi(data, process, i, 1);
		else
			ft_pipe_multi(data, process, i, 0);
		proclst = proclst->next;
		i++;
	}
	close(data->stdinfd);
	i = 0;
	while (i < (size * 2))
	{
		waitpid(-1, &status, 0);
		wait_pid2(status);
		i++;
	}
}
