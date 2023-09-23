/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:41:21 by ivanderw          #+#    #+#             */
/*   Updated: 2023/03/21 18:43:21 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
NAME
     strlcat -- size-bounded string concatenation

SYNOPSIS
     #include <string.h>

    size_t
     strlcat(char * restrict dst, const char * restrict src, size_t dstsize);

DESCRIPTION
     strlcpy() and strlcat() take the full size of the destination buffer 
	 and guarantee NUL-ter-
     mination if there is room.  Note that room for the NUL should be included
	 in dstsize.

     strlcat() appends string src to the end of dst.  It will append at most 
	 dstsize -
     strlen(dst) - 1 characters.  It will then NUL-terminate, unless dstsize 
	 is 0 or the original dst string was longer than dstsize 
	 (in practice this should not happen as it means that either dstsize 
	 is incorrect or that dst is not a proper string).

     If the src and dst strings overlap, the behavior is undefined.

RETURN VALUES
     Like snprintf(3), the strlcpy() and strlcat() functions return the 
	 total length of the
     string they tried to create.  For strlcpy() that means the length of src. 
	 For strlcat() that means the initial length of dst plus the length of src.

     If the return value is >= dstsize, the output string has been truncated. 
	 It is the
     caller's responsibility to handle this.
*/
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_length;
	size_t	src_length;
	size_t	bytes_to_copy;

	dst_length = ft_strlen(dst);
	src_length = ft_strlen(src);
	if (dst_length >= dstsize || dstsize == 0)
		return (dstsize + src_length);
	else
	{
		if ((src_length + dst_length) < dstsize)
			bytes_to_copy = src_length + 1;
		else
		{
			bytes_to_copy = dstsize - dst_length - 1;
			dst[dst_length + bytes_to_copy] = '\0';
		}	
		ft_memcpy(dst + dst_length, src, bytes_to_copy);
	}
	return (dst_length + src_length);
}
