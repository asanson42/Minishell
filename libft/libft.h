/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanson <asanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 16:43:18 by asanson           #+#    #+#             */
/*   Updated: 2022/03/17 18:06:56 by mj               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	struct s_list	*previous;
	void			*content;
	struct s_list	*next;
}		t_list;

void	*ft_calloc(size_t nmemb, size_t size);
int		ft_atoi(const char *str);
char            *ft_itoa(int n);
int		ft_isalnum(int c);
int		ft_isprint(int c);
int		ft_isspec(int c);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *s1, const char *s2, size_t n);
int		ft_dlstsize(t_list *dlst);
char	*ft_strcat(char *dest, const char *src);
t_list	*ft_dlstnew(void *content);
t_list	*ft_dlstlast(t_list *dlst);
void	ft_dlstadd_back(t_list **adlst, t_list *dnew);
void	ft_dlstadd_front(t_list **adlst, t_list *dnew);
void	ft_dlstdelone(t_list *dlst, void (*del)(void *));
void	ft_dlstclear(t_list **dlst, void (*del)(void *));
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(char *s);
char	*ft_strdup(const char *s1);
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *b, int c, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char    **ft_strsplit(char const *s, char c);
char	**ft_split(char const *s, char c);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
int		ft_strequ(const char *s1, const char *s2);
char	*ft_strchr(const char *s, int c);
size_t	get_char_by_index(char *str, char c);
void	ft_free_array(char **array);
#endif
