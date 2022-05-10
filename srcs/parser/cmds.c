/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mj <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 16:50:16 by mj                #+#    #+#             */
/*   Updated: 2022/04/30 17:31:31 by mj               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	check_quotes(char *str, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

char	*no_quotes(char *str, char c)
{
	char	*new;
	int		count;
	int		i;
	int		j;

	count = check_quotes(str, c);
	new = malloc(sizeof(char) * ((ft_strlen(str) - count) + 1));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == c)
			i++;
		else
		{
			new[j] = str[i];
			j++;
			i++;
		}
	}
	new[j] = '\0';
	return (new);
}

char	*no_quotes_2(char *str)
{
	char	*new;
	int		i;
	int		j;

	new = malloc(sizeof(char) * ((ft_strlen(str) - \
	(check_quotes(str, '\"') - check_quotes(str, '\''))) + 1));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			i++;
		else
		{
			new[j] = str[i];
			j++;
			i++;
		}
	}
	new[j] = '\0';
	return (new);
}

char	*new_cmd(char *tokenstr, t_data *data)
{
	int		db_quotes;
	int		sp_quotes;
	int		dollar;

	db_quotes = ft_check_double(tokenstr);
	sp_quotes = ft_check_simple(tokenstr);
	dollar = ft_check_dollar_exp(tokenstr);
	if (ft_value_found(tokenstr, data))
		return (ft_strdup(tokenstr));
	else if (sp_quotes == 0 && db_quotes == 0)
		return (ft_strdup(tokenstr));
	else if (db_quotes == 2 && sp_quotes == 0 && dollar == 0)
		return (no_quotes(tokenstr, '\"'));
	else if (db_quotes == 2 && sp_quotes == 0 && dollar == 1)
		return (ft_strdup(tokenstr));
	else if (db_quotes == 0 && sp_quotes == 2)
		return (no_quotes(tokenstr, '\''));
	else if (db_quotes == 2 && sp_quotes == 2 && ft_check_first(tokenstr) == 2)
		return (no_quotes(tokenstr, '\"'));
	else if (db_quotes == 2 && sp_quotes == 2 && ft_check_first(tokenstr) == 1)
		return (no_quotes(tokenstr, '\''));
	else
		return (no_quotes_2(tokenstr));
}
