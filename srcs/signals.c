#include "lexer.h"

void	sig_int2(int sig)
{
	if (sig == 2)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sig_int(int sig)
{
	if (sig == 2)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		write(2, "Quit (core dumped\n", ft_strlen("Quit (core dumped\n"));
		exit(1);
	}	
}
