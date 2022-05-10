/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mj <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 16:30:12 by mj                #+#    #+#             */
/*   Updated: 2022/05/09 19:08:37 by mj               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	search_env(t_data *data, char *cmd)
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
	t_list	*envlst;

	envlst = (*exenv);
	if (!cmd)
		return ;
	while (envlst)
	{
		current = (t_env *)envlst->content;
		if (ft_strcmp(cmd, current->var + 1) == 0)
		{
			current = unset_cmd(current, envlst, exenv);
			return ;
		}
		else if (ft_strcmp(cmd, current->value + 1) == 0)
		{
			current = unset_cmd(current, envlst, exenv);
			return ;
		}
		printf("env->var: %s, env->value: %s\n", current->var, current->value);
		envlst = envlst->next;
	}
	search_env(data, cmd);
	data->succes = 1;
	return ;
}
