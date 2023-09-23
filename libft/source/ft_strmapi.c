/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 19:43:31 by ivanderw          #+#    #+#             */
/*   Updated: 2023/03/18 20:14:49 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
PROTOTYPE
	char *ft_strmapi(char const *s, char (*f)(unsigned int, char));

PARAMETERS
	s: 	The string on which to iterate
	f:	The function to apply to each character.

RETURN VALUE
	The string created from the successive applications of 'f'
	Returns NULL if the allocation fails.

EXTERNAL FUNCTS
	malloc

DESCRIPTION
	Applies the function 'f' to each character of the string 's', and passing
	its index as the first argument to create a new string (with malloc(3) 
	resulting from successive applications of 'f'.
*/
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*out;
	size_t	i;

	if (!s)
		return (NULL);
	out = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!out)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		out[i] = f(i, s[i]);
		i++;
	}
	out[i] = '\0';
	return (out);
}
