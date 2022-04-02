#include "lexer.h"

void	lexer_and_parser(t_data *data)
{
        //LEXER
        find_token(data->cmdline, &data->tokenlst, &data->lexer);
	t_list  *lst = data->tokenlst;
        t_token *current;
        while (lst)
        {
                current = (t_token*)lst->content;
                lst = lst->next;
        }  
	//EXPAND
	ft_expand(data->tokenlst, data);
	//PARSER
	if (data->tokenlst)
        {
		if (ft_check_tokens(data->tokenlst))
                {
                        printf("bash: Syntax Error\n");
                        free_data(data);
                }
                if (ft_proclst(data->tokenlst, &data->proclst))
                        free_data(data);
	//CMDS
		run_cmds(data);
	}
}
