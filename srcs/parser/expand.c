#include "lexer.h"

char	*ft_split_value(char *env, char *cmd, int size)
{
	int len = 0;
	int i = 0;
	char *value;

	while (env[size] != '=')
                size++;
	len = ft_strlen(env + (size + 1));
	value = malloc(sizeof(char) * (len + 1));
	if (!value)
		return (NULL);
	size++;
	while (env[(size + i)])
	{
		value[i] = env[(size + i)];
		i++;
	}
	value[i] = '\0';
	return (value);
}

char *find_value_env(char *cmd, char **env)
{
	char *split;
	int i = 0;
	int j = 0;
	int k = 0;

	while (cmd[i] == '\'' || cmd[i] == '\"' || cmd[i] == '$')
                        i++;
        while (ft_isalnum(cmd[i + j]))
                j++;
        while(env[k])
        {
                if (ft_strncmp(cmd + i, env[k], j) == 0)
                {
                        split = ft_split_value(env[k], cmd + i, j);
                        if (!split)
                        {
                                free(split);
                                return (NULL);
                        }
                        return (split);
                }
                k++;
        }
	free(split);
	return (NULL);
}

char	*find_value_envlist(char *cmd, t_list *envlist)
{
	t_env *current;
	char *value;
	int i = 0;

	while (cmd[i] == '\'' || cmd[i] == '\"')
		i++;
	while (envlist)
	{
		current = (t_env*)envlist->content;
		if (ft_strcmp(cmd + i, current->var) == 0)
		{
			value = current->value;
			return (value);
		}
		envlist = envlist->next;
	}
	return (NULL);
}

char	*ft_find_value(char *cmd, char **env, t_list *envlist)
{
	char *value;
	int find = 0;

	find = ft_env_exist(cmd, env, envlist);

	if (find == 1)
	{
		value = find_value_env(cmd, env);
		return (value);
	}
	else if (find == 2)
	{
		value = find_value_envlist(cmd, envlist);
		return (value);
	}
}

int ft_find_envlist(char *cmd, t_list *envlist)
{
	int i = 0;
	t_env *current;

	while (cmd[i] == '\'' || cmd[i] == '\"')
		i++;
	while (envlist)
	{
		current = (t_env*)envlist->content;
		if (ft_strcmp(cmd, current->var) == 0)
			return (1);
		envlist = envlist->next;
	}
	return (0);
}

int ft_env_exist(char *cmd, char **env, t_list *envlist)
{
	int i = 0;
	int j = 0;
	int k = 0;

	while (cmd[i] == '\'' || cmd[i] == '\"' || cmd[i] == '$')
			i++;
	while (ft_isalnum(cmd[i + j]))
		j++;
	while(env[k])
	{
		if (ft_strncmp(cmd + i, env[k], j) == 0)
			return (1);
		k++;
	}
	if (envlist != NULL)
		if (ft_find_envlist(cmd, envlist))
			return (2);
	else
		return (0);
	return (0);
}

int	ft_check_dollar(char *cmd)
{
	int i;

	if (cmd)
	{
		i = 0;
		while (cmd[i] == '\'' || cmd[i] == '\"')
			i++;
		if (cmd[i] == '$')
			return (1);
		else
			return (0);
	}
	return (0);
}

int	ft_check_simple(char *cmd)
{
	int i = 0;
	int count = 0;

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
	int i = 0;
	int count = 0;

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
	int i = 0;
	int j = 0;

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
	char *new_value;
	int i = 0;
	int len = 0;

	free(value);
	len = ft_strlen(cmd);
	if (cmd[i] == '\'')
		i++;
	new_value = ft_substr(cmd, i, (len - 2));
	free(current->tokenstr);
	current->tokenstr = new_value;
	
}

void	ft_replace_double(t_token *current, char *value, char *cmd)
{
	char *new_value;
        int i = 0;
        int j = 0;
	int k = 0;
	int len = 0;

	len = ft_strlen(value) + 2;
	new_value = malloc(sizeof(char) * (len + 1));

	while (cmd[i] == '\"')
		i++;
	while (cmd[i] == '\'')
	{
		new_value[j] = cmd[i];
		i++;
		j++;
	}
	while (value[k])
	{
		new_value[j] = value[k];
		j++;
		k++;
	}
	new_value[j] = '\'';
	j++;
	new_value[j] = '\0';
	free(value);
	free(current->tokenstr);
	current->tokenstr = new_value;
}

void	ft_end_value(t_token *current, char *value, char *cmd)
{
	int	double_quotes = 0;
	int	simple_quotes = 0;
	int	check_first = 0;

	simple_quotes = ft_check_simple(current->tokenstr);
	double_quotes = ft_check_double(current->tokenstr);
	if (simple_quotes == 2 && double_quotes == 2)
		check_first = ft_check_first(current->tokenstr);
	if (simple_quotes == 0 && double_quotes == 0)
		ft_replace_value(current, value);
	else if (simple_quotes == 2 && double_quotes == 0)
		return ;
	else if (simple_quotes == 0 && double_quotes == 2)
		ft_replace_value(current, value);
	else if (simple_quotes == 2 && double_quotes == 2 && check_first == 1)
		ft_replace_simple(current, value, cmd);
	else if (simple_quotes == 2 && double_quotes == 2 && check_first == 2)
		ft_replace_double(current, value, cmd);		
}

void	ft_exit_status(t_token *current)
{
	char *value;

	value = ft_itoa(g_exit_status);
	free(current->tokenstr);
	current->tokenstr = value;	
}

void	ft_empty_value(char *cmd, t_token *current, t_list *tokenlst)
{
	int d_quotes = 0;
	int s_quotes = 0;
	int check_first = 0;
	int ret = 0;

	s_quotes = ft_check_simple(cmd);
	d_quotes = ft_check_double(cmd);
	
	if (s_quotes == 0 && d_quotes == 0)
		ret = 1;
	else if (s_quotes == 2 && d_quotes == 0)
		ret = 0;
	else if (s_quotes == 0 && d_quotes == 2)
		ret = 1;
	else if (s_quotes == 2 || d_quotes == 2)
		check_first = ft_check_first(cmd);
	if (check_first == 2)
		ret = 1;
	else if (check_first == 1)
		ret = 0;
	if (ret == 1)
	{
		free(current->tokenstr);
		current->tokenstr = NULL;
		current = NULL;
	}
}

void	ft_expand(t_list *tokenlst, t_data *data)
{
	t_token *current;
	char *value;

	while (tokenlst)
	{
		current = (t_token*)tokenlst->content;
		if (current->tokentype == 3)
			return ;
		if (current->tokentype == 0)
		{
			if (ft_strcmp(current->tokenstr, "$?") == 0)
				ft_exit_status(current);
			if (ft_check_dollar(current->tokenstr))
			{
				if (ft_env_exist(current->tokenstr, data->env, data->envlist))
				{
					value = ft_find_value(current->tokenstr, data->env, data->envlist);
					if (value == NULL)
						return ;
					else
						return (ft_end_value(current, value, current->tokenstr));

				}
				else
					if(ft_strcmp("export", ((t_token*)tokenlst->previous->content)->tokenstr) == 0)
						return ;
					return (ft_empty_value(current->tokenstr, current, tokenlst));
			}
		}
		tokenlst = tokenlst->next;
	}
	return ;
}
