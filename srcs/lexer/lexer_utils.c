/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanson <asanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 13:59:11 by asanson           #+#    #+#             */
/*   Updated: 2022/02/27 18:22:54 by asanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	ft_secondquote(char *cmdline, int i)
{
	char	quote;

	quote = cmdline[i++];
	while (cmdline[i])
		if (cmdline[i++] == quote)
			return (1);
	return (0);
}

int	ft_quote(char *cmdline, int quote, int i)
{
	if (cmdline[i] == ' ')
	{
		if (quote == 1)
			return (1);
		else
			return (0);
	}
	if (cmdline[i] == 39 || cmdline[i] == 34)
	{
		if (quote == 1 || ft_secondquote(cmdline, i) == 0)
			return (0);
		else
			return (1);
	}
	return (quote);
}

static int	ft_sstoken(char *cmdline, t_list **tokenlst, int i, int test)
{
	int	toklen;

	toklen = 0;
	while (cmdline[i + toklen]
		&& (cmdline[i + toklen] == '<' || cmdline[i + toklen] == '>'))
		toklen++;
	if (toklen <= 2)
	{
		if (test == 1)
			create_token(cmdline, tokenlst, toklen, i);
		return (toklen);
	}
	return (-1);
}

int	ft_spetoken(char *cmdline, t_list **tokenlst, int i, int test)
{
	int	toklen;

	toklen = 0;
	if (cmdline[i] == '|')
	{
		while (cmdline[i + toklen] && cmdline[i + toklen] == '|')
			toklen++;
		if (toklen == 1)
		{
			if (test == 1)
				create_token(cmdline, tokenlst, toklen, i);
			return (toklen);
		}
	}
	else if (cmdline[i] == '<' || cmdline[i] == '>')
		return (ft_sstoken(cmdline, tokenlst, i, test));
	return (-1);
}

void	find_tokstate(t_token *token)
{
	if (ft_strcmp(token->tokenstr, "|") == 0)
		token->tokentype = 5;
	else if (ft_strcmp(token->tokenstr, "<") == 0)
		token->tokentype = 1;
	else if (ft_strcmp(token->tokenstr, ">") == 0)
		token->tokentype = 2;
	else if (ft_strcmp(token->tokenstr, "<<") == 0)
		token->tokentype = 3;
	else if (ft_strcmp(token->tokenstr, ">>") == 0)
		token->tokentype = 4;
	else
		token->tokentype = 0;
}
