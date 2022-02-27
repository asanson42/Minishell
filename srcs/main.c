#include "lexer.h"

int	ft_size_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs[i] && strs[i][0] != '\0')
		i++;
	return (i);
}

void    ft_free_strs(char **strs, int index)
{
        int i = 0;

	if (strs != NULL)
	{
        	while (i < index)
		{
                	free(strs[i]);
			i++;
		}
        	free(strs);
		strs = NULL;
	}
}

static char     **envdup(char **envp)
{
        char    **new;
        int     i;

        i = 0;
        while (envp[i])
                i++;
        //printf("i = %d\n", i);
        new = malloc(sizeof(char *) * (i + 1));
        if (!new)
                return (NULL);
        i = 0;
        while (envp[i])
        {
                new[i] = ft_strdup(envp[i]);
                i++;
        }
        new[i] = NULL;
        return (new);
}

static void	init_data(t_data *data, char **envp)
{
	data->env = NULL;
	data->prompt = NULL;	
	data->cmdline = NULL;
	data->tokenlst = NULL;
	data->proclst = NULL;
	data->envlist = NULL;
	data->env = envdup(envp);
	data->mode = 1;
	data->stdfd[0] = 0;
	data->stdfd[1] = 1;
	data->lexer.toklen = 0;
	data->lexer.quote = 0;
	data->lexer.dbquote = 0;
}

static void     print_envp(char **env)
{
        int     i = 0;

        while (env[i])
                printf("%s\n", env[i++]);
}

static char *get_line(t_data *data)
{
	char *line;

	line = NULL;
	if (line)
	{
		free(line);
		line = NULL;
	}
	line = readline(get_prompt(data));
	if (line)
		add_history(line);
	return (line);
}

int	ft_end(char *line, t_data *data, int mode)
{
	if (mode = 0)
		printf("Déconnexion\n");
	else
	{
		if (line)
		{
			free(line);
			line = NULL;
		}
	}
	if (data->prompt != NULL)
	{
		free(data->prompt);
		data->prompt = NULL;
	}
	ft_free_strs(data->env, ft_size_strs(data->env));
	rl_clear_history();
	return (1);
}	

int	main(int argc, char **argv, char **envp)
{
	t_data data;
	char *line = NULL;

	if (argc > 1)
	{
		printf("Error: too many args\n");
		return (0);
	}
	init_data(&data, envp);
	signal(SIGINT, sig_int);
	signal(SIGQUIT, SIG_IGN);
	while (data.mode)
	{
		line = get_line(&data);
		if (!line)
		{
			data.mode = 0;
			return (ft_end(line, &data, data.mode));
			//break ;
		}
		data.cmdline = line;
		signal(SIGINT, sig_int);
		signal(SIGQUIT, SIG_IGN);
		lexer_and_parser(&data);
		free(line);
	}
	//return(ft_end(line, &data, 1));
	return (0);
}
