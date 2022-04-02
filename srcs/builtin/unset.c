/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanson <asanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 13:53:00 by asanson           #+#    #+#             */
/*   Updated: 2022/03/28 15:43:43 by mj               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void    print_envlist(t_list *envlist)
{
        t_env *env;

        while (envlist)
        {
                env = (t_env*)envlist->content;
                printf("env->var: %s\n", env->var);
		printf("env->value: %s\n", env->value);
		envlist = envlist->next;
        }
}


static void	*unset_cmd(t_env *env, t_list *exenv, t_list **envlist)
{
	t_list *first = *envlist;
	t_list *tmp = exenv;
	t_list *tmp2;

	if ((ft_strcmp(((t_env*)first->content)->value, ((t_env*)tmp->content)->value) == 0))
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
	if (env->value)
		env->value = NULL;
	if (env->var)
	{
		free(env->var);
		env->var = NULL;
	}
	free(env);
	env = NULL;
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



void	ft_unset(char *cmd, t_list **exenv, t_data *data)
{
	t_env	*current;
	t_list *envlst;

	envlst = (*exenv);

	if (!cmd)
		return ;
	while (envlst)
	{
		current = (t_env *)envlst->content;
		if (ft_strcmp(cmd, current->var) == 0)
		{
			current = unset_cmd(current, envlst, exenv);
			return ;
		}
		else if (ft_strcmp(cmd, current->value) == 0)
		{
			current = unset_cmd(current, envlst, exenv);
			return ;
		}
		envlst = envlst->next;
	}
	search_env(data, cmd);
	return ;
}
