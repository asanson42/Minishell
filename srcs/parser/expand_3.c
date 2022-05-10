/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mj <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 21:59:23 by mj                #+#    #+#             */
/*   Updated: 2022/04/28 22:27:41 by mj               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

extern int	g_exit_status;

int	ft_check_simple(char *cmd)
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
	if (count <= 1)
		return (0);
	else
		return (2);
}

int	ft_check_double(char *cmd)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\"')
			count++;
		i++;
	}
	if (count <= 1)
		return (0);
	else
		return (2);
}

int	ft_check_first(char *cmd)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (cmd[i])
	{
		j = i + 1;
		if (cmd[i] == '\'' && cmd[j] == '\"')
			return (1);
		else if (cmd[i] == '\"' && cmd[j] == '\'')
			return (2);
		else
			return (0);
		i++;
	}
	return (0);
}

void	ft_replace_value(t_token *current, char *value)
{
	free(current->tokenstr);
	current->tokenstr = value;
}

void	ft_replace_simple(t_token *current, char *value, char *cmd)
{
	char	*new_value;
	int		i;
	int		len;

	i = 0;
	free(value);
	len = ft_strlen(cmd);
	if (cmd[i] == '\'')
		i++;
	new_value = ft_substr(cmd, i, (len - 2));
	free(current->tokenstr);
	current->tokenstr = new_value;
}
