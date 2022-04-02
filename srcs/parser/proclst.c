#include "lexer.h"

static int	add_process(t_process *process, t_list **proclst)
{
	t_list *new = NULL;

	new = ft_dlstnew(process);
	if (new == NULL)
	{
		//clear_process();
		return (1);
	}
	ft_dlstadd_back(proclst, new);
	return (0);
}

int	ft_proclst(t_list *tokenlst, t_list **proclst)
{
	t_process *process;

	while (tokenlst)
	{
		process = malloc(sizeof(*process));
		if (process == NULL)
			return (1);
		ft_bzero(process, sizeof(*process));
		if (ft_rdirlst(tokenlst, &process->rdirlst, process))
		{
			//clear_process(process);
			return (1);
		}
		if (ft_cmds(&tokenlst, &process->cmds))
		{
			//clear_process(process);
			return (1);
		}
		if (tokenlst && ((t_token*)tokenlst->content)->tokentype == 5)
			tokenlst = tokenlst->next;
		if (add_process(process, proclst))
			return (1);
	}
	return (0);
}
