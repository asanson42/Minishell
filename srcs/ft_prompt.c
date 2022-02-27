#include "lexer.h"

static void     print_lst(t_list *tokenlst)
{
        int i = 0;
        int size;
        t_token *current;

        size = ft_dlstsize(tokenlst);
        //printf("size_lst: %d\n", size);
        while (i < size)
        {
                current = tokenlst->content;
                printf("tokenstr: %s => tokentype: %d\n", current->tokenstr, current->tokentype);
                tokenlst = tokenlst->next;
                i++;
        }
        printf("\n");
}

void	lexer_and_parser(t_data *data)
{
	int size_tokenlst = 0;

        //LEXER
        find_token(data->cmdline, &data->tokenlst, &data->lexer);
	size_tokenlst = ft_dlstsize(data->tokenlst);
	t_list  *lst = data->tokenlst;
        t_token *current;
        while (lst)
        {
                current = (t_token*)lst->content;
                lst = lst->next;
        }
        //PARSER
	if (data->tokenlst)
        {
		if (ft_check_tokens(data->tokenlst))
                {
                        printf("bash: Syntax Error\n");
                        //free_all();
                }
                if (ft_proclst(data->tokenlst, &data->proclst))
                {
                        //free_all();
                        exit(1);
                }
	//CMDS
		run_cmds(data);
        //CLEAR
		ft_dlstclear(&data->tokenlst, NULL);
                ft_dlstclear(&data->proclst, NULL);
	}
}

char *get_prompt(t_data *data)
{
	char cwd[1024];
	//char *tmp;
	int i;

	getcwd(cwd, sizeof(cwd));
	data->prompt = malloc(sizeof(char) * (sizeof(cwd) + 3));
	i = 0;
	while (cwd[i])
	{
		data->prompt[i] = cwd[i];
		i++;
	}
	data->prompt[i++] = '~';
	data->prompt[i++] = ' ';
	data->prompt[i++] = '\0';
	//tmp = ft_strjoin(cwd, "~ ");
	return (data->prompt);
}
