/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mj <marvin@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 16:57:15 by mj                #+#    #+#             */
/*   Updated: 2022/04/05 16:59:50 by mj               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(const char *s, char c)
{
	int		number;
	int		i;

	i = 0;
	number = 0;
	while (*s)
	{
		if (i == 1 && *s == c)
			i = 0;
		if (i == 0 && *s != c)
		{
			i = 1;
			number++;
		}
		s++;
	}
	return (number);
}

void	spliting(int words, char const *s, char c, char **strs)
{
	int	j;
	int	i;
	int	start;

	j = -1;
	i = 0;
	while (++j < words)
	{
		while (s[i] && s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		strs[j] = ft_substr(s, start, i - start);
		i++;
	}
	strs[j] = NULL;
}

char	**ft_strsplit(char const *s, char c)
{
	int		words;
	char	**strs;

	if (!s || !c)
		return (NULL);
	words = ft_count_words(s, c);
	strs = malloc((sizeof(char *) * (words + 1)));
	if (strs == NULL)
		return (NULL);
	spliting(words, s, c, strs);
	return (strs);
}
