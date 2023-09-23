/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 12:15:38 by ivanderw          #+#    #+#             */
/*   Updated: 2023/03/18 17:50:18 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
NAME
	ft_strtrim

PROTOTYPE
	char *ft_strtrim(char const *s1, char const *set);

PARAMETERS
	s1:		The string to be trimmed
	set:	The reference set of characters to trim

RETURN VALUE
	The trimmed string.
	NULL if the allocation fails.

EXTERNAL FUNCTS
	malloc

DESCRIPTION
	Allocates (with malloc(3)) and returns a copy of 's1' with the characters
	specified ins 'set' removed from the beginning and the end of the string.
*/
#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trim;
	size_t	start;
	size_t	end;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	trim = ft_substr(s1, start, end - start);
	if (!trim)
		return (NULL);
	return (trim);
}
