/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_run_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mj <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 18:14:58 by mj                #+#    #+#             */
/*   Updated: 2022/04/30 18:19:41 by mj               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

extern int	g_exit_status;

int	count_quotes(char *line, char c)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == c)
			j++;
		i++;
	}
	return (j);
}

char	*get_new_line(char *line, char *value, char *new_line)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	while (line[i] == '\'' || line[i] == '\"')
		new_line[j++] = line[i++];
	while (value[k])
		new_line[j++] = value[k++];
	while (line[i] == '$' || line[i] >= 'a' \
			&& line[i] <= 'z' || line[i] >= 'A' && line[i] <= 'Z')
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

char	*get_value(char *line, char **env, t_list *envlist)
{
	char	*new_line;
	char	*value;
	int		d_q;
	int		s_q;
	int		len;

	d_q = 0;
	s_q = 0;
	len = 0;
	value = ft_find_value(line, env, envlist);
	s_q = count_quotes(line, '\'');
	d_q += count_quotes(line, '\"');
	len = ft_strlen(value);
	new_line = malloc(sizeof(char) * ((d_q + s_q + len) + 1));
	new_line = get_new_line(line, value, new_line);
	return (new_line);
}

char	*get_empty(char *line)
{
	char	*new_line;
	int		d_q;
	int		s_q;
	int		i;
	int		j;

	d_q = count_quotes(line, '\"');
	s_q = count_quotes(line, '\'');
	i = 0;
	j = 0;
	if (d_q > 0 || s_q > 0)
	{
		new_line = malloc(sizeof(char) * ((d_q + s_q) + 1));
		while (line[i] == '\'' || line[i] == '\"')
			new_line[j++] = line[i++];
		while (line[i] >= 'a' && line[i] <= 'z' \
				|| line[i] >= 'A' && line[i] <= 'Z' || line[i] == '$')
			i++;
		while (line[i] == '\'' || line[i] == '\"')
			new_line[j++] = line[i++];
	}
	else
		return (" ");
	new_line[j] = '\0';
	return (new_line);
}

int	ft_check_dollar(char *line)
{
	int		i;

	i = 0;
	while (line[i] == '\"' || line[i] == '\'')
		i++;
	if (line[i] == '$')
		return (1);
	else
		return (0);
}
