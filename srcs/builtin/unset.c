/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanson <asanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 13:53:00 by asanson           #+#    #+#             */
/*   Updated: 2022/02/27 13:53:02 by asanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	*unset_cmd(t_env *env)
{
	free(env->value);
	free(env->var);
	return (NULL);
}

static int	ft_is_env(char **env, char *cmd)
{
	int	i;
	int	len;

	len = ft_strlen(cmd);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], cmd, len) == 0)
			return (1);
		i++;
	}
	return (0);
}

static void	ft_free_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		free(env[i++]);
	free(env);
	env = NULL;
}

static void	search_env(t_data *data, char *cmd)
{
	char	**new;
	int		i;
	int		j;
	int		len;

	i = 0;
	len = ft_strlen(cmd);
	if (ft_is_env(data->env, cmd) == 0)
		return ;
	while (data->env[i])
		i++;
	new = malloc(sizeof(char *) * (i));
	i = 0;
	j = 0;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], cmd, len) != 0)
			new[j++] = ft_strdup(data->env[i]);
		i++;
	}
	new[j] = NULL;
	ft_free_env(data->env);
	data->env = new;
}

void	ft_unset(char *cmd, t_list *exenv, t_data *data)
{
	t_env	*current;

	while (exenv)
	{
		current = (t_env *)exenv->content;
		if (ft_strcmp(cmd, current->var) == 0)
		{
			current = unset_cmd(current);
			ft_dlstdelone(exenv, NULL);
			return ;
		}
		exenv = exenv->next;
	}
	search_env(data, cmd);
}
