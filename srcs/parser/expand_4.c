/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mj <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 22:53:44 by mj                #+#    #+#             */
/*   Updated: 2022/04/28 22:53:45 by mj               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

extern int	g_exit_status;

static int	count_db(char *cmd)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'')
			count++;
		i++;
	}
	return (count);
}

void	ft_replace_double(t_token *current, char *value, char *cmd)
{
	char	*new_value;
	int		i;
	int		j;
	int		k;
	int		l;

	i = 0;
	k = 0;
	l = 0;
	new_value = malloc(sizeof(char) * ((ft_strlen(value) + count_db(cmd)) + 1));
	while (cmd[i] == '\"')
		i++;
	j = i;
	while (cmd[j] == '\'')
		new_value[k++] = cmd[j++];
	while (value[l])
		new_value[k++] = value[l++];
	while (j++ != count_db(cmd) + 1)
		new_value[k++] = '\'';
	new_value[k] = '\0';
	free(value);
	free(current->tokenstr);
	current->tokenstr = new_value;
}
