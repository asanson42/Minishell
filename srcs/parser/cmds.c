#include "lexer.h"

static int	size_cmds(t_list *tokenlst)
{
	int size;
	t_token *current;

	size = 0;

	while (tokenlst)
	{
		current = (t_token*)tokenlst->content;
		if (current->tokentype == 0)
			if (tokenlst->previous == NULL)
				size++;
			else if (tokenlst->previous != NULL)
			{
				if (((t_token*)tokenlst->previous->content)->tokentype < 1 || ((t_token*)tokenlst->previous->content)->tokentype > 4)
					size++;
			}
		if (current->tokentype == 5)
			break ;
		tokenlst = tokenlst->next;
	}
	return (size);
}


static int	ft_tab_cmds(t_list **tokenlst, char **cmds)
{
	t_token *current;
	int i;

	i = 0;
	while (*tokenlst)
	{
		current = (*tokenlst)->content;
		if (current->tokentype == 5)
			break ;
		if (current->tokentype == 0)
		{
			if ((*tokenlst)->previous == NULL)
			{
				cmds[i] = ft_strdup(current->tokenstr);
				if (cmds[i] == NULL)
					return (1);
				i++;
			}
                        else if ((*tokenlst)->previous != NULL)
                        {
                                if (((t_token*)(*tokenlst)->previous->content)->tokentype < 1 || ((t_token*)(*tokenlst)->previous->content)->tokentype > 4)
				{
                                        cmds[i] = ft_strdup(current->tokenstr);
					if (cmds[i] == NULL)
						return (1);
					i++;
				}
                        }
		}
		*tokenlst = (*tokenlst)->next;
	}
	return (0);
}

int	ft_cmds(t_list **tokenlst, char ***cmds)
{
	int size = 0;
	char **new_cmds = NULL;

	size = size_cmds(*tokenlst);
	new_cmds = malloc(sizeof(*new_cmds) * (size + 1));
	if (new_cmds == NULL)
		return (1);
	new_cmds[size] = NULL;
	if (ft_tab_cmds(tokenlst, new_cmds) > 0)
		return (1);
	*cmds = new_cmds;
	return (0);	
}
