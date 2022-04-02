#include "lexer.h"

void    free_rdir(t_list **rdirlst)
{
        t_rdir *rdir;
        t_list *tmp;

        while (*rdirlst)
        {
                tmp = (*rdirlst)->next;
                rdir = (*rdirlst)->content;
                if (rdir->name)
                        free(rdir->name);
                free(rdir);
                free(*rdirlst);
                (*rdirlst) = tmp;
        }
}

void    free_process(t_list **proclst)
{
        t_process *process;
        t_list *tmp;

        while (*proclst)
       { 
                tmp = (*proclst)->next;
                process = (*proclst)->content;
                if (process->cmds)
                        ft_free_strs(process->cmds, ft_size_strs(process->cmds));
                if (ft_dlstsize(process->rdirlst) >= 1)
                        free_rdir(&process->rdirlst);
                free(process);
                free(*proclst);
                (*proclst) = tmp;
        }
}

int	ft_in_envlist(char *tokenstr, t_list *envlist)
{
	t_env *current;

	if (envlist != NULL)
	{
		while (envlist)
		{
			current = (t_env*)envlist->content;
			if (ft_strcmp(tokenstr, current->var) == 0)
				return (1);
			if (ft_strcmp(tokenstr, current->value) == 0)
				return (1);
			envlist = envlist->next;
		}

	}
	return (0);
}

void    free_token(t_list **tokenlst, t_list *envlist)
{
        t_token *token;
        t_list *tmp;

        while (*tokenlst)
        {
                tmp = (*tokenlst)->next;
                token = (*tokenlst)->content;
                if (token->tokenstr && ft_in_envlist(token->tokenstr, envlist) == 0)
                        free(token->tokenstr);
		else if (ft_strcmp(token->tokenstr, " ") == 0)
			free(token->tokenstr);
                free(token);
                free((*tokenlst));
                (*tokenlst) = tmp;
        }
}

void	free_envlist(t_list **envlist)
{
	t_env *env;
	t_list *tmp;

	while (*envlist)
	{
		tmp = (*envlist)->next;
		env = (*envlist)->content;
		if (env->var)
			free(env->var);
		if (env->value)
			free(env->value);
		free(env);
		free((*envlist));
		(*envlist) = tmp;
	}
}

void	print_tokenlst(t_list *tokenlst)
{
	t_token *current;

	printf("size tokenlst: %d\n", ft_dlstsize(tokenlst));	
	printf("TOKENLST:\n");
	while (tokenlst)
	{
		current = (t_token*)tokenlst->content;
		printf("tokenstr: %s|\n", current->tokenstr);
		tokenlst = tokenlst->next;
	}
}

void	print_envlst(t_list *envlist)
{
	t_env *env;
	
	printf("size envlist: %d\n", ft_dlstsize(envlist));
	printf("ENVLIST\n");
	while (envlist)
	{
		env = (t_env*)envlist->content;
		printf("env->var: %s\n", env->var);
		printf("env->value: %s\n", env->value);
		envlist = envlist->next;
	}
}

void    free_data(t_data *data)
{
        if (ft_dlstsize(data->proclst) >= 1)
        {
                free_process(&data->proclst);
                free(data->proclst);
		data->proclst = NULL;
        }
	if (data->tokenlst)
	{
		free_token(&data->tokenlst, data->envlist);
		free(data->tokenlst);
		data->tokenlst = NULL;
	}
}

void    free_end_mode(char *line, t_data *data)
{
        if (line)
                free(line);
        free_data(data);
}

