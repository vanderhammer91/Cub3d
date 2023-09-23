/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 12:03:56 by ivanderw          #+#    #+#             */
/*   Updated: 2023/03/15 14:50:45 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
NAME
	calloc
SYNOPSIS
	void *
	calloc(size_t count, size_t size);

DESCRIPTION
	The malloc(), calloc(), valloc(), realloc(), and reallocf() functions 
	allocate memory.  The allocated memory is aligned such
     that it can be used for any data type, including AltiVec- and 
	 SSE-related types.  The aligned_alloc() function allocates mem-
     ory with the requested alignment.  The free() function frees 
	 allocations that were created via the preceding allocation func-
     tions.

	The calloc() function contiguously allocates enough space for count 
	objects that are size bytes of memory each and returns a
    pointer to the allocated memory.  The allocated memory is filled 
	with bytes of value zero.

RETURN VALUES
     If successful, calloc() function return a pointer to allocated memory.  
	 If there is an error, they return a NULL pointer and set errno to ENOMEM.
*/
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*output;
	size_t	size_count;

	size_count = count * size;
	output = malloc(size_count);
	if (output == 0)
		return (0);
	ft_bzero(output, size_count);
	return (output);
}
