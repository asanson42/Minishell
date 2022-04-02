#include "lexer.h"

int	check_word(char *str)
{
	int i = 0;
	int j = 0;

	while (str[i])
	{
		j = i + 1;
		if (str[i] == '<')
			if (str[j] == '>')
				return (1);
		if (str[i] == '>')
			if (str[j] == '<')
				return (1);
		if (str[i] == '|')
			if (str[j] == '|')
				return (1);
		i++;
	}
	return (0);
	
}

int ft_check_tokens(t_list *lst)
{
	t_token *current;
	t_token *first;

	first = lst->content;
	if (first->tokentype == 5 || (first->tokentype != 0 && lst->next == NULL))
		return (1);
	while (lst)	
	{
		if (((t_token*)lst->content)->tokenstr)
		{
			current = lst->content;
			if (current->tokentype == 5 && (lst->next == NULL || ((t_token*)lst->next->content)->tokentype == 5))
				return (1);
			if ((current->tokentype >= 1 && current->tokentype <= 4))
				if (lst->next == NULL || ((t_token*)lst->next->content)->tokentype != 0)
					return (1);
			if (current->tokentype == 0)
				if (check_word(current->tokenstr) != 0)
					return (1);
		}
		lst = lst->next;
	}
	if (current->tokentype >= 1 && current->tokentype <= 5)
		return (1);
	return (0);
}
