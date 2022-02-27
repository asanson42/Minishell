#include "lexer.h"

// FONCTIONS TEMPORAIRES PRINTF

static void     print_cmds(char **cmds)
{
        int i = 0;

	//printf("cmds: \n");
        while (cmds[i])
	{
                printf("cmds: %s\n", cmds[i]);
		i++;
	}
}

static void     print_rdirlst(t_list *rdirlst)
{
	//printf("rdir: \n");
        while (rdirlst)
        {
                printf("type: %d\n", ((t_rdir*)rdirlst->content)->type);
                printf("name: %s\n", ((t_rdir*)rdirlst->content)->name);
                rdirlst = rdirlst->next;
        }
}

static void      print_proclst(t_list *lst)
{
        t_process *process;

        while (lst)
        {
                process = (t_process*)lst->content;
		print_cmds(process->cmds);
		print_rdirlst(process->rdirlst);
		printf("\n");
		lst = lst->next;
        }
}

//////////////////////////////////////////////////////////////////


static int	add_process(t_process *process, t_list **proclst)
{
	t_list *new;

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
		//print_rdirlst(process->rdirlst);
		if (ft_cmds(&tokenlst, &process->cmds))
		{
			//clear_process(process);
			return (1);
		}
		//print_cmds(process->cmds);
		if (tokenlst && ((t_token*)tokenlst->content)->tokentype == 5)
			tokenlst = tokenlst->next;
		if (add_process(process, proclst))
			return (1);
	}
	//print_proclst(*proclst);
	return (0);
}
