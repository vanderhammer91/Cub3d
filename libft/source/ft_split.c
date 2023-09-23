/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 17:01:54 by ivanderw          #+#    #+#             */
/*   Updated: 2023/03/21 12:33:27 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
NAME
	ft_split

PROTOTYPE
	char	**ft_split(char const *s, char c);

PARAMETERS
	s:	The string to be split.
	c:	The delimiter character.

RETURN
	The array of new strings resulting from the split
	NULL if the allocation fails

EXTERNAL FUNCTIONS
	malloc, free

DESCRIPTION
	Allocates (with malloc(3)) and returns an array of strings obtained by 
	splitting 's' using the character 'c' as a delimiter. The array must end 
	with a NULL pointer.
*/
#include "libft.h"

static size_t	get_word_count(char const *s, char c)
{
	size_t	word_count;
	size_t	is_word;

	is_word = 0;
	word_count = 0;
	while (*s)
	{
		if (*s != c && is_word == 0)
		{	
			is_word = 1;
			word_count++;
		}
		else if (*s == c)
			is_word = 0;
		s++;
	}
	return (word_count);
}

static char	*ft_strndup(const char *s, size_t n)
{
	char	*out;
	size_t	i;

	out = (char *)malloc(n + 1);
	if (!out)
		return (NULL);
	i = 0;
	while (i < n && s[i])
	{
		out[i] = s[i];
		i++;
	}
	while (i <= n)
		out[i++] = 0;
	return (out);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	word_count;
	size_t	i;
	size_t	j;

	if (!s)
		return (0);
	word_count = get_word_count(s, c);
		split = malloc(sizeof(char *) * (word_count + 1));
	if (!split)
		return (0);
	i = 0;
	j = 0;
	while (i < word_count)
	{
		while (s[j] == c)
			j++;
		s = &s[j];
		j = 0;
		while (s[j] != c && s[j])
			j++;
		split[i++] = ft_strndup(s, j);
	}
	split[i] = 0;
	return (split);
}
