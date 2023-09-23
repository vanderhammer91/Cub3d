/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:51:38 by ivanderw          #+#    #+#             */
/*   Updated: 2023/03/08 14:30:15 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 SYNOPSIS
     #include <ctype.h>

     int
     isprint(int c);

DESCRIPTION
     The isprint() function tests for any printing character, including space
     (` ').  The value of the argument must be representable as an unsigned
     char or the value of EOF.

RETURN VALUES
     The isprint() function returns zero if the character tests false and
     returns non-zero if the character tests true.
 */

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}
