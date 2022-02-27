/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanson <asanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 13:52:18 by asanson           #+#    #+#             */
/*   Updated: 2022/02/27 13:52:23 by asanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	is_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int	already_set(char *var, t_list *exenv)
{
	t_env	*current;

	while (exenv)
	{
		current = (t_env *)exenv->content;
		if (ft_strcmp(var, current->var) == 0)
			return (1);
		exenv = exenv->next;
	}
	return (0);
}

char	**ft_export_split(char *cmd)
{
	char	**split;
	int		index;
	int		i;
	int		j;

	index = is_equal(cmd);
	split = malloc(sizeof(char *) * (2));
	split[0] = malloc(sizeof(char) * (index + 1));
	split[1] = malloc(sizeof(char) * (ft_strlen(cmd) - index + 1));
	i = 0;
	while (cmd[i] != '=')
	{
		split[0][i] = cmd[i];
		i++;
	}
	split[0][i] = '\0';
	j = 0;
	while (cmd[i])
		split[1][j++] = cmd[i++];
	split[1][i] = '\0';
	return (split);
}

char	**ft_no_split(char *cmd)
{
	char	**split;
	int		i;

	split = NULL;
	split = malloc(sizeof(char *) * (2));
	split[0] = malloc(sizeof(char) * (ft_strlen(cmd) + 1));
	split[1] = NULL;
	i = 0;
	while (cmd[i])
	{
		split[0][i] = cmd[i];
		i++;
	}
	split[0][i] = '\0';
	return (split);
}

void	set_value(char **split, t_list *exenv)
{
	t_env	*current;

	while (exenv)
	{
		current = (t_env *)exenv->content;
		if (ft_strcmp(split[0], current->var) == 0)
		{
			if (current->value != NULL)
				free(current->value);
			current->value = ft_strdup(split[1]);
			current->size = ft_strlen(split[0]) + ft_strlen(split[1]);
			return ;
		}
		exenv = exenv->next;
	}
}
