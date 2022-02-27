#include "lexer.h"

static void ft_fork2(t_data *data, t_process *process, int stdinfd, int cnt, int next_lst)
{
	t_rdir *rdir;
	char *pathname;
	int i = 0;

	if (next_lst >= 1)
		dup2(data->pipefd[1], STDOUT_FILENO);
	if (cnt != 0)
		dup2(stdinfd, STDIN_FILENO);
	close(stdinfd);
	close(data->pipefd[0]);
	close(data->pipefd[1]);
	while (process->rdirlst)
	{
		rdir = (t_rdir*)process->rdirlst->content;
		if (rdir->type == 0 || rdir->type == 2)
                        ft_dup2_in(data, rdir);
                else if (rdir->type == 1 || rdir->type == 3)
                        ft_dup2_out(data, rdir);
                process->rdirlst = process->rdirlst->next;
	}
	if (is_builtins(process->cmds[i]))
		run_built(process->cmds[i], process->cmds, data);
        else
        {

		pathname = find_path(process->cmds[i], data);
		if (execve(pathname, process->cmds, data->env))
			error_exec();
	}
}

static void	ft_pipe_multi(t_data *data, t_process *process, int stdinfd, int cnt, int next_lst)
{
	pid_t pid;

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
		ft_fork2(data, process, stdinfd, cnt, next_lst);
	}
	else
	{
		dup2(data->pipefd[0], stdinfd);
		close(data->pipefd[0]);
		close(data->pipefd[1]);
	}
}

void	ft_run_multi(t_data *data, t_list *proclst, int size)
{
	int	stdinfd;
	int status;
	t_process *process;
	int i = 0;

	stdinfd = dup(STDIN_FILENO);
	while (i < size && proclst)
	{
		process = (t_process*)proclst->content;
		if (proclst->next != NULL)
			ft_pipe_multi(data, process, stdinfd, i, 1);
		else
			ft_pipe_multi(data, process, stdinfd, i, 0);
		proclst = proclst->next;
		i++;
	}
	close(stdinfd);
	i = 0;
	while (i < (size * 2))
	{
		waitpid(-1, &status, 0);
		i++;
	}
}
