/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanson <asanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 16:21:39 by asanson           #+#    #+#             */
/*   Updated: 2022/05/10 17:55:23 by mmahias          ###   ########.fr       */
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
	int	spec;
}		t_lexer;

typedef struct s_data
{
	char		**env;
	char		*prompt;
	int			pipefd[2];
	int			stdfd[2];
	int			stdinfd;
	char		*cmdline;
	int			mode;
	int			succes;
	t_list		*tokenlst;
	t_list		*proclst;
	t_list		*envlist;
	t_lexer		lexer;
}		t_data;

// PROMPT
void	lexer_and_parser(t_data *data);

// LEXER
int		ft_is_null(t_token *token);
int		ft_secondquote(char *cmdline, int i);
int		ft_quote(char *cmdline, int quote, int i);
void	find_tokstate(t_token *current);
void	create_token(char *cmdline, t_list **tokenlst, int len, int index);
int		ft_spetoken(char *cmdline, t_list **tokenlst, int i, t_lexer *lexer);
int		find_token(char *cmdline, t_list **tokenlst, t_lexer *d);
int		ft_check_tokens(t_list *lst);

// EXPAND
char	*find_value_env(char *cmd, char **env);
char	*find_value_envlist(char *cmd, t_list *envlist);
int		ft_check_dollar_exp(char *cmd);
int		ft_check_double(char *cmd);
int		ft_check_simple(char *cmd);
int		ft_check_first(char *cmd);
void	ft_replace_value(t_token *current, char *value);
void	ft_replace_simple(t_token *current, char *value, char *cmd);
void	ft_replace_double(t_token *current, char *value, char *cmd);
int		ft_env_exist(char *cmd, char **env, t_list *envlist);
char	*ft_find_value(char *cmd, char **env, t_list *envlist);
void	ft_empty_value(char *cmd, t_token *current, t_list *tokenlst);
void	ft_expand(t_list *tokenlst, t_data *data);

// PARSER
int		check_close(char *str, char c);
t_rdir	*ft_trdir(t_token *current, t_token *next, t_process *process);
int		ft_rdirlst(t_list *tokenlst, t_list **rdirlst, t_process *process);
int		ft_value_found(char *tokenstr, t_data *data);
char	*new_cmd(char *tokenstr, t_data *data);
int		size_cmds(t_list *tokenlst);
int		ft_cmds(t_list **tokenlst, char ***process, \
t_data *data, t_list *rdirlst);
int		ft_proclst(t_list *tokenlst, t_list **proclst, t_data *data);

// CMDS
void	run_cmds(t_data *data);

// EXEC
char	*get_value(char *line, char **env, t_list *envlist);
char	*get_empty(char *line);
int		ft_check_dollar(char *line);
int		is_builtins(char *cmd);
int		len_path(char **path);
int		ft_size_strs(char **strs);
char	*is_access(char *cmd, char *path);
int		find_access(char *cmd, char *path);
char	*find_path(char *cmd, t_data *data);
int		wait_pid(pid_t pid);
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

void	*unset_cmd(t_env *env, t_list *exenv, t_list **envlist);
int		ft_is_env(char **env, char *cmd);
void	ft_free_env(char **env);
void	ft_unset(char *cmd, t_list **exenv, t_data *data);

void	print_env(char **env, int fd);
void	ft_env(t_data *data, t_list *envx, int fd);

void	ft_pwd(char **env, int fd, t_data *data);
void	ft_echo(char **cmds, int fd, t_data *data);

ssize_t	find_env(char *arg, char **env);
size_t	get_envs_count(char **envp);
char	*get_env(char *arg, char **env);
char	*add_home_path(char *path, char **envp);
char	**realloc_envs(size_t size, char **envp);
int		modify(char *new_env, char **envp, size_t len, ssize_t i);
int		ft_cd(char **args, t_data *data);
void	ft_exit(char **cmds, t_data *data);
void	run_built(char *cmd, char **cmds, t_data *data);

//SIGNAUX
void	sig_int(int sig);
void	sig_int2(int sig);

//CLOSE && ERRORS
void	ft_error_command(char *cmd, char **path, t_data *data);
void	error_exec(void);
void	error_pid(void);
void	ft_free_strs(char **strs, int index);
int		ft_end(char *line, t_data *data, int mode);
void	free_rdir(t_list **rdirlst);
void	free_process(t_list **proclst);
void	free_token(t_list **tokenlst, t_list *envlist);
void	free_envlist(t_list **envlist);
void	free_data(t_data *data);
void	free_end_mode(char *line, t_data *data);
void	ft_clean_all(t_data *data);

#endif
