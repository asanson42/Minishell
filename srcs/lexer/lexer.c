/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanson <asanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 13:55:43 by asanson           #+#    #+#             */
/*   Updated: 2022/05/06 17:55:17 by asanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	ft_is_null(t_token *token)
{
	int	i;

	i = 0;
	if (!token->tokenstr)
		return (1);
	while (token->tokenstr[i] && (token->tokenstr[i] == ' '
			|| token->tokenstr[i] == '\t'))
		i++;
	if (token->tokenstr[i] == '\0')
		return (1);
	return (0);
}

void	create_token(char *cmdline, t_list **tokenlst, int len, int index)
{
	int		i;
	t_list	*new;
	t_token	*current;

	if (len <= 0)
		return ;
	new = NULL;
	current = NULL;
	i = 0;
	current = (t_token *)malloc(sizeof(t_token));
	current->tokenstr = malloc(sizeof(char) * (len + 1));
	if (!current->tokenstr)
		return ;
	while (i < len && cmdline[index + i])
	{
		current->tokenstr[i] = cmdline[index + i];
		i++;
	}
	current->tokenstr[len] = '\0';
	current->tokenlen = len;
	find_tokstate(current);
	new = ft_dlstnew(current);
	ft_dlstadd_back(tokenlst, new);
}

static void	create_spe_token(char *cmd, t_list **toklst, t_lexer *d, int index)
{
	if (d->quote == 0 && cmd[index] == 39)
		create_token(cmd, toklst, d->toklen, index);
	else if (d->dbquote == 0 && cmd[index] == 34)
		create_token(cmd, toklst, d->toklen, index);
	else
		create_token(cmd, toklst, d->toklen, index);
}

static int	check_cmdending(char *cmd, int index)
{
	int	i;

	i = 0;
	while (cmd[index + i])
	{
		if (cmd[index + i] != ' ')
			return (index);
		i++;
	}
	return (index + i);
}

int	find_token(char *cmd, t_list **tokenlst, t_lexer *d)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		d->toklen = 0;
		while (cmd[i] && cmd[i] == ' ' && d->quote == 0 && d->dbquote == 0)
			i++;
		if (cmd[i] && ft_isspec(cmd[i]) == 1)
			d->toklen += ft_spetoken(cmd, tokenlst, i, d);
		if (ft_isspec(cmd[i]) == 0 || d->spec == 1)
		{
			while (cmd[i + d->toklen] && ((cmd[i + d->toklen] != ' '
						|| d->quote == 1 || d->dbquote == 1) || d->spec == 1))
			{
				d->quote = ft_quote(cmd, d->quote, i + d->toklen);
				d->dbquote = ft_quote(cmd, d->dbquote, i + d->toklen);
				d->toklen++;
			}
			create_spe_token(cmd, tokenlst, d, i);
		}
		i += check_cmdending(cmd + i, d->toklen);
	}
	return (1);
}
