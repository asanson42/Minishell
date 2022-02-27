/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanson <asanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 16:21:39 by asanson           #+#    #+#             */
/*   Updated: 2022/02/27 18:23:19 by asanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include "./../libft/libft.h"

typedef enum e_tokentype
{
	WORD = 0,
	RDIR_IN,
	RDIR_OUT,
	RDIR_HEREDOC,
	RDIR_A_OUT,
	PIPE
}		t_tokentype;

typedef enum e_rdirtype
{
	IN,
	OUT,
	HEREDOC,
	A_OUT
}		t_rdirtype;

typedef struct s_rdir
{
	t_rdirtype	type;
	char		*name;
	int			fd;	
}		t_rdir;

typedef struct s_process
{
	char	**cmds;
	t_list	*rdirlst;
}		t_process;

typedef struct s_token
{
	char		*tokenstr;
	t_tokentype	tokentype;
	size_t		tokenlen;
}		t_token;

typedef struct s_env
{
	char	*var;
	char	*value;
	int		size;
}		t_env;

typedef struct s_lexer
{
	int	toklen;
	int	quote;
	int	dbquote;
}		t_lexer;

typedef struct s_data
{
	char		**env;
	char		*prompt;
	int			pipefd[2];
	int			stdfd[2];
	char		*cmdline;
	int			mode;
	t_list		*tokenlst;
	t_list		*proclst;
	t_list		*envlist;
	t_lexer		lexer;
}		t_data;

// PROMPT
char	*get_prompt(t_data *data);
void	lexer_and_parser(t_data *data);

// LEXER
int		ft_secondquote(char *cmdline, int i);
int		ft_quote(char *cmdline, int quote, int i);
void	find_tokstate(t_token *current);
void	create_token(char *cmdline, t_list **tokenlst, int len, int index);
int		ft_spetoken(char *cmdline, t_list **tokenlst, int i, int test);
int		find_token(char *cmdline, t_list **tokenlst, t_lexer *d);
int		ft_check_tokens(t_list *lst);

// PARSER
t_rdir	*ft_trdir(t_token *current, t_token *next, t_process *process);
int		ft_rdirlst(t_list *tokenlst, t_list **rdirlst, t_process *process);
int		ft_cmds(t_list **tokenlst, char ***process);
int		ft_proclst(t_list *tokenlst, t_list **proclst);

// CMDS
void	run_cmds(t_data *data);

// EXEC
int		is_builtins(char *cmd);
int		len_path(char **path);
int		ft_size_strs(char **strs);
int		find_access(char *cmd, char *path);
char	*find_path(char *cmd, t_data *data);
void	ft_dup2_in(t_data *data, t_rdir *rdir);
void	ft_dup2_out(t_data *data, t_rdir *rdir);
void	ft_exec(t_data *data, t_process *process);
void	ft_run_multi(t_data *data, t_list *proclst, int size);

//BUILTIN
int		is_equal(char *str);
int		already_set(char *var, t_list *exenv);
char	**ft_export_split(char *cmd);
char	**ft_no_split(char *cmd);
void	set_value(char **split, t_list *exenv);
void	ft_export(char *cmd, t_list **exenvi, t_data *data, int fd);

void	ft_unset(char *cmd, t_list *exenvi, t_data *data);

void	print_env(char **env, int fd);
void	ft_env(t_data *data, t_list *envx, int fd);

void	ft_pwd(char **env, int fd);
void	ft_echo(char *cmd, int n, int fd);

ssize_t	find_env(char *arg, char **env);
size_t	get_envs_count(char **envp);
char	*get_env(char *arg, char **env);
char	*add_home_path(char *path, char **envp);
char	**realloc_envs(size_t size, char **envp);
int		modify(char *new_env, char **envp, size_t len, ssize_t i);
int		ft_cd(char **args, t_data *data);
void	run_built(char *cmd, char **cmds, t_data *data);

//SIGNAUX
void	sig_int(int sig);
void	sig_int2(int sig);

//CLOSE
void	error_exec(void);
void	error_pid(void);
void	ft_free_strs(char **strs, int index);
int		ft_end(char *line, t_data *data, int mode);
void	ft_clean_all(t_data *data);

#endif
