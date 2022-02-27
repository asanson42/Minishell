/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanson <asanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 16:30:45 by asanson           #+#    #+#             */
/*   Updated: 2022/02/27 16:30:46 by asanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && (!(s[i] == c)))
			count++;
		while (s[i] && (!(s[i] == c)))
			i++;
	}
	return (count);
}

static int	ft_size_words(char const *s, char c, int i)
{
	int	size;

	size = 0;
	while (s[i] && (!(s[i] == c)))
	{
		size++;
		i++;
	}
	return (size);
}

char	**ft_free(char **strs, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	int		index;
	int		i;
	int		j;

	i = 0;
	index = 0;
	if (!s)
		return (NULL);
	strs = malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	while (s[i] && (index < ft_count_words(s, c)))
	{
		while (s[i] == c)
			i++;
		strs[index] = malloc(sizeof(char) * ft_size_words(s, c, i) + 1);
		if (!strs[index])
			return (ft_free(strs, index));
		j = 0;
		while (s[i] && (!(s[i] == c)))
			strs[index][j++] = s[i++];
		strs[index][j] = '\0';
		index++;
	}
	strs[index] = 0;
	return (strs);
}
