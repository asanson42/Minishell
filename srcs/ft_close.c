#include "lexer.h"

void	error_exec(void)
{
	char *error;

	error = strerror(errno);
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}

void	error_pid(void)
{
	char *error;

	error = strerror(errno);
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
}

void	ft_clean_all(t_data *data)
{
	printf("Déconnexion\n");
	ft_end(data->cmdline, data, 1);
	exit(0);
}
