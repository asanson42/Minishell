#include "lexer.h"

static void	here_doc(t_data *data, t_rdir *rdir)
{
	int mode = 1;
	char *line;

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
			exit(1);
		}
	}
	else if (rdir->type == 2)
		here_doc(data, rdir);
	dup2(data->pipefd[1], data->stdfd[0]);
	close(data->pipefd[1]);
}

void	 ft_dup2_out(t_data *data, t_rdir *rdir)
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

static void	ft_fork(t_data *data, t_process *process)
{
	t_rdir *rdir;
	int i = 0;
	char *pathname;

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

static void	ft_pipe_redir(t_data *data, t_process *process)
{
	pid_t pid;
	int status;

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
		waitpid(pid, &status, 0);
		signal(SIGINT, sig_int);
		signal(SIGQUIT, SIG_DFL);
	}
}

static int	size_proclst(t_list *lst)
{
	int i = 0;

	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

void	run_cmds(t_data *data)
{
	t_process *process = NULL;
	t_rdir *rdir = NULL;
	int i;
	int size = 0;
	
	size = size_proclst(data->proclst);
	if (size > 1)
               ft_run_multi(data, data->proclst, size);
	else
	{
		while (data->proclst)
		{	
			process = (t_process*)data->proclst->content;
			if (process->rdirlst)
				ft_pipe_redir(data, process);
			else if (is_builtins(process->cmds[0]))
				run_built(process->cmds[0], process->cmds, data);
			else
				ft_exec(data, process);
			data->proclst = data->proclst->next;
		}
	}
}
