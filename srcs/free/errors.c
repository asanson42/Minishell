#include "lexer.h"

void	ft_maj_exit_status(t_list *envlist)
{
	t_env *current;
	char *new_value;

	//printf("maj exit_status: %d\n", g_exit_status);
	while (envlist)
	{
		current = (t_env*)envlist->content;
		//printf("var: %s\n", current->var);
		if (ft_strcmp(current->var, "$?") == 0)
		{
			new_value = ft_itoa(g_exit_status);
			free(current->value);
			current->value = new_value;
		}
		envlist = envlist->next;
	}
}

void	ft_error_command(char *cmd, char **path, t_data *data)
{
	if (path != NULL)
		ft_free_strs(path, ft_size_strs(path));
	ft_putstr_fd(cmd, 1);
	ft_putstr_fd(": command not found\n", 1);
	g_exit_status = 127;
	//ft_maj_exit_status(data->envlist);
	exit(1);
}
