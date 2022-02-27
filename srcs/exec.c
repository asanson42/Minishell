#include "lexer.h"

static int	ft_count_words(const char *s, char c)
{
	int		number;
	int		i;

	i = 0;
	number = 0;
	while (*s)
	{
		if (i == 1 && *s == c)
			i = 0;
		if (i == 0 && *s != c)
		{
			i = 1;
			number++;
		}
		s++;
	}
	return (number);
}

void	spliting(int words, char const *s, char c, char **tab)
{
	int	j;
	int	i;
	int	start;

	j = -1;
	i = 0;
	while (++j < words)
	{
		while (s[i] && s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		tab[j] = ft_substr(s, start, i - start);
		i++;
	}
	tab[j] = NULL;
}

char	**ft_strsplit(char const *s, char c)
{
	int		words;
	char	**tab;

	if (!s || !c)
		return (NULL);
	words = ft_count_words(s, c);
	tab = malloc((sizeof(char *) * (words + 1)));
	if (tab == NULL)
		return (NULL);
	spliting(words, s, c, tab);
	return (tab);
}

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
		//return (bad_cmd(cmd));
		exit(1);
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
		//free_all;
		exit(1);
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
