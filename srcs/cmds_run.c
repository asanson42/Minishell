#include "lexer.h"

static int count_quotes(char *line, char c)
{
	int i = 0;
	int j = 0;

	while (line[i])
	{
		if (line[i] == c)
			j++;
		i++;
	}
	return (j);
}

static char *get_new_line(char *line, char *value, char *new_line)
{
	int i = 0;
	int j = 0;
	int k = 0;

	while (line[i] == '\'' || line[i] == '\"')
        {
                new_line[j] = line[i];
                j++;
                i++;
        }
        while (value[k])
        {
                new_line[j] = value[k];
                j++;
                k++;
        }
        while (line[i] == '$' || line[i] >= 'a' && line[i] <= 'z' || line[i] >= 'A' && line[i] <= 'Z')
                i++;
        while (line[i] == '\'' || line[i] == '\"')
        {
                new_line[j] = line[i];
                j++;
                i++;
        }
        new_line[j] = '\0';
	return (new_line);
}

static char	*get_value(char *line, char **env, t_list *envlist)
{
	char *new_line;
	char *value;
	int d_q = 0;
	int s_q = 0;
	int len = 0;

	value = ft_find_value(line, env, envlist);
	s_q = count_quotes(line, '\'');
	d_q += count_quotes(line, '\"');
	len = ft_strlen(value);
	new_line = malloc(sizeof(char) * ((d_q + s_q + len) + 1));
	new_line = get_new_line(line, value, new_line);
	return (new_line);	
}

static char *get_empty(char *line)
{
	char *new_line;
	int d_q = 0;
	int s_q = 0;
	int i = 0;
	int j = 0;

	d_q = count_quotes(line, '\"');
	s_q = count_quotes(line, '\'');
	if (d_q > 0 || s_q > 0)
	{
		new_line = malloc(sizeof(char) * ((d_q + s_q) + 1));
		while (line[i] == '\'' || line[i] == '\"')
		{
			new_line[j] = line[i];
			i++;
			j++;
		}
		while (line[i] >= 'a' && line[i] <= 'z' || line[i] >= 'A' && line[i] <= 'Z' || line[i] == '$') 
			i++;
		while (line[i] == '\'' || line[i] == '\"')
		{
			new_line[j] = line[i];
			i++;
			j++;
		}
	}
	else
		return (" ");
	new_line[j] = '\0';
	return (new_line);
}

static 	int	ft_check_dollar(char *line)
{
	int i = 0;
	
	while (line[i] == '\"' || line[i] == '\'')
		i++;
	if (line[i] == '$')
		return (1);
	else
		return (0);
}

char	*ft_find_var(char *line, t_data *data)
{
	char *new_line;

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
		//line = ft_find_var(line, data);
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
	t_list *lst;
	
	size = ft_dlstsize(data->proclst);
	if (size > 1)
               ft_run_multi(data, data->proclst, size);
	else
	{
		lst = data->proclst;
		while (lst)
		{	
			process = (t_process*)lst->content;
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
