/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 14:53:59 by ivanderw          #+#    #+#             */
/*   Updated: 2023/03/16 11:35:42 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
Function name: 
	ft_substr

Prototype:
	char *ft_substr(char const *s, unsigned int start, size_t len);

Parameters 
	s: The string from which to create the substring.

	start: The start index of the substring in the string ’s’.

	len: The maximum length of the substring.

Return value: 
	The substring.

	NULL if the allocation fails.

External functs. 
	malloc

Description:
	Allocates (with malloc(3)) and returns a substring from the string ’s’.
	The substring begins at index ’start’ and is of maximum size ’len’
*/
#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*output;
	size_t	i;
	size_t	s_len;

	if (!s)
		return ((char *)s);
	s_len = ft_strlen(s);
	if (start > s_len)
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	output = (char *) malloc(len + 1);
	if (!(output))
		return (NULL);
	i = 0;
	while (i < len)
	{
		output[i] = s[i + start];
		i++;
	}
	output[i] = '\0';
	return (output);
}
