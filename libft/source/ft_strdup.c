/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 14:37:57 by ivanderw          #+#    #+#             */
/*   Updated: 2023/03/15 17:00:09 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
NAME
     strdup, strndup -- save a copy of a string

LIBRARY
     Standard C Library (libc, -lc)

SYNOPSIS
     #include <string.h>

     char *
     strdup(const char *s1);

     char *
     strndup(const char *s1, size_t n);

DESCRIPTION
     The strdup() function allocates sufficient memory for a copy of the 
	 string s1, does the copy, and returns a pointer to it.
     The pointer may subsequently be used as an argument to the function 
	 free(3).

     If insufficient memory is available, NULL is returned and errno is set 
	 to ENOMEM.
	 */
#include "libft.h"

char	*ft_strdup(char *src)
{
	char	*output;
	int		i;

	output = (char *) malloc(ft_strlen(src) + 1);
	if (!(output))
		return (NULL);
	i = 0;
	while (src[i] != '\0')
	{
		output[i] = src[i];
		i++;
	}
	output[i] = '\0';
	return (output);
}
