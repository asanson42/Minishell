/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanson <asanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 13:53:00 by asanson           #+#    #+#             */
/*   Updated: 2022/04/25 20:01:44 by mj               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	print_envlist(t_list *envlist)
{
	t_env	*env;

	while (envlist)
	{
		env = (t_env *)envlist->content;
		printf("env->var: %s\n", env->var);
		printf("env->value: %s\n", env->value);
		envlist = envlist->next;
	}
}

static void	free_utils(t_env *env)
{
	if (env->value)
		env->value = NULL;
	if (env->var)
	{
		free(env->var);
		env->var = NULL;
	}
}

void	*unset_cmd(t_env *env, t_list *exenv, t_list **envlist)
{
	t_list	*first;
	t_list	*tmp;
	t_list	*tmp2;

	first = *envlist;
	tmp = exenv;
	if ((ft_strcmp(((t_env *)first->content)->value, \
		((t_env *)tmp->content)->value) == 0))
	{
		first->previous = NULL;
		*envlist = first->next;
		free(tmp);
	}
	else
	{
		tmp2 = exenv->previous;
		if (exenv->next != NULL)
			tmp2->next = exenv->next;
		else
			tmp2->next = NULL;
		free(tmp);
	}
	free_utils(env);
	free(env);
	return (NULL);
}

int	ft_is_env(char **env, char *cmd)
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

void	ft_free_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		free(env[i++]);
	free(env);
	env = NULL;
}
