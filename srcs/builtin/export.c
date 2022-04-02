/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanson <asanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 13:52:29 by asanson           #+#    #+#             */
/*   Updated: 2022/03/11 20:26:25 by asanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	free_split(char **split)
{
	free(split[0]);
	free(split[1]);
	free(split);
	split = NULL;
}

void	other_export(char *cmd, t_list **exenv, t_env *env, char **split)
{
	t_list	*new;

	new = NULL;
	env = (t_env *)malloc(sizeof(t_env));
	env->var = ft_strdup(split[0]);
	if (split[1])
		env->value = ft_strdup(split[1]);
	else
		env->value = NULL;
	env->size = ft_strlen(cmd);
	new = ft_dlstnew(env);
	ft_dlstadd_back(exenv, new);
}

void	ft_print_export(t_list *exenv, t_data *data, int fd)
{
	t_env	*current;

	print_env(data->env, fd);
	while (exenv)
	{
		current = (t_env *)exenv->content;
		if (current->var != 0)
			ft_putstr_fd(current->var, fd);
		if (current->value != NULL)
			ft_putstr_fd(current->value, fd);
		ft_putchar_fd('\n', fd);
		exenv = exenv->next;
	}
}

void	ft_export(char *cmd, t_list **exenv, t_data *data, int fd)
{
	t_list	*new;
	t_env	*env;
	char	**split;

	new = NULL;
	env = NULL;
	split = NULL;
	if (!cmd)
	{
		ft_print_export(*exenv, data, fd);
		return ;
	}
	if (is_equal(cmd) == -1)
		split = ft_no_split(cmd);
	else
		split = ft_export_split(cmd);
	if (already_set(split[0], *exenv) == 1)
	{
		if (split[1] == NULL)
			return ;
		set_value(split, *exenv);
	}
	else
		other_export(cmd, exenv, env, split);
	free_split(split);
}
