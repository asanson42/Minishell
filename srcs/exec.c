#include "lexer.h"

char	*is_access(char *cmd, char *path)
{
	char *slash;
	char *new;

	slash = ft_strjoin(path, "/");
	if (slash == NULL)
		return (NULL);
	new = ft_strjoin(slash, cmd);
	free(slash);
	if (new == NULL)
		return (NULL);
	return (new);
}

int	find_access(char *cmd, char *path)
{
	char	*f_access;

	f_access = is_access(cmd, path);
	if (f_access == NULL)
		return (0);
	if (access(f_access, X_OK) == 0)
	{
		free(f_access);
		return (1);
	}
	free(f_access);
	return (0);
}

char	*find_path(char *cmd, t_data *data)
{
	char	**path;
	char	**split_path;
	char 	*path_acces;
	int 	i = 0;
	int	ret;

	if (cmd && (cmd[0] == '.' || cmd[0] == '/'))
		return (cmd);
	while (!(ft_strncmp(data->env[i], "PATH=", 5) == 0))
		i++;
	split_path = ft_strsplit(data->env[i], ':');
	if (split_path == NULL)
		ft_error_command(cmd, NULL, data);
	i = 0;
	while (split_path[i] && cmd[0] != '\0')
	{
		ret = find_access(cmd, split_path[i]);
		if (ret == 1)
		{
			path_acces = is_access(cmd, split_path[i]);
			ft_free_strs(split_path, ft_size_strs(split_path));
			return (path_acces);		
		}
		i++;
	}
	if (ret == 0)
		ft_error_command(cmd, split_path, data);
	return (cmd);
	
}

int	is_builtins(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "export") == 0)
		return (1);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd, "env") == 0)
		return (1);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	else
		return (0);
}

void	ft_exec(t_data *data, t_process *process)
{
	pid_t pid;
	char	*pathname;
	int status;
	int i = 0;	
	
	pid = fork();
	if (pid == 0)
	{
	
                pathname = find_path(process->cmds[i], data);
		if (execve(pathname, process->cmds, data->env))
			error_exec();
        }
	if (pid < 0)
		error_pid();
	else
	{
		signal(SIGINT, sig_int2);
		signal(SIGQUIT, SIG_IGN);
		waitpid(pid, &status, 0);
		signal(SIGINT, sig_int);
		signal(SIGQUIT, SIG_IGN);
	}
}
