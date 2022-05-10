/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mj <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 17:00:55 by mj                #+#    #+#             */
/*   Updated: 2022/05/09 20:27:30 by mj               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	g_exit_status;

int	ft_size_strs(char **strs)
{
	int		i;

	i = 0;
	while (strs[i] && strs[i][0] != '\0')
		i++;
	return (i);
}

static char	**envdup(char **envp)
{
	char	**new;
	int		i;

	i = 0;
	while (envp[i])
		i++;
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
	data->succes = 0;
	data->stdfd[0] = 0;
	data->stdfd[1] = 1;
	data->stdinfd = 0;
	data->lexer.toklen = 0;
	data->lexer.quote = 0;
	data->lexer.dbquote = 0;
	data->lexer.spec = 0;
	g_exit_status = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*line;

	line = NULL;
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
		line = readline("minishell~ ");
		add_history(line);
		if (line == NULL)
			return (ft_end(line, &data, 0));
		data.cmdline = line;
		signal(SIGINT, sig_int);
		signal(SIGQUIT, SIG_IGN);
		lexer_and_parser(&data);
		free_end_mode(line, &data);
	}
	return (ft_end(line, &data, 1));
}
