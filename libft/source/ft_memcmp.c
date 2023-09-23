/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:02:12 by ivanderw          #+#    #+#             */
/*   Updated: 2023/03/14 18:14:23 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
 * NAME
     memcmp -- compare byte string

LIBRARY
     Standard C Library (libc, -lc)

SYNOPSIS
     #include <string.h>

     int
     memcmp(const void *s1, const void *s2, size_t n);

DESCRIPTION
     The memcmp() function compares byte string s1 against byte string s2.
   	 Both strings are assumed to be n bytes long.

RETURN VALUES
     The memcmp() function returns zero if the two strings are identical, 
	 otherwise returns the difference between the first two differing bytes 
	 (treated as unsigned char values, so that `\200' is greater than 
	 `\0', for example).  
	 Zero-length strings are always identical. 
	 This behavior is not required by C and portable code should only depend 
	 on the sign of the returned value.
*/
#include <string.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	unsigned char		*my_s1;
	const unsigned char	*my_s2;

	i = 0;
	my_s1 = (unsigned char *)s1;
	my_s2 = (const unsigned char *)s2;
	while (i < n)
	{
		if (my_s1[i] != my_s2[i])
			return (my_s1[i] - my_s2[i]);
		i++;
	}
	return (0);
}
