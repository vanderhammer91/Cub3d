/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:44:12 by ivanderw          #+#    #+#             */
/*   Updated: 2023/03/21 13:28:36 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
NAME
     memcpy -- copy memory area

LIBRARY
     Standard C Library (libc, -lc)

SYNOPSIS
     #include <string.h>

     void *
     memcpy(void *restrict dst, const void *restrict src, size_t n);

DESCRIPTION
     The memcpy() function copies n bytes from memory area src to memory area 
	 dst.  If dst and src overlap,
     behavior is undefined.  Applications in which dst and src might overlap 
	 should use memmove(3) instead.

RETURN VALUES
     The memcpy() function returns the original value of dst.
*/
#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*d;
	const char	*s;

	if (dst == NULL && src == NULL)
		return (NULL);
	if (n == 0)
		return (dst);
	d = (char *) dst;
	s = (const char *) src;
	while (n--)
		*d++ = *s++;
	if (dst)
		return (dst);
	return (NULL);
}
