/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 13:50:42 by ivanderw          #+#    #+#             */
/*   Updated: 2023/03/08 14:28:50 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
 
SYNOPSIS
     #include <ctype.h>

     int
     isdigit(int c);

     int
     isnumber(int c);

DESCRIPTION
     The isdigit() function tests for a decimal digit character.  Regardless
     of locale, this includes the following characters only:

     ``0''         ``1''         ``2''         ``3''         ``4''
     ``5''         ``6''         ``7''         ``8''         ``9''

     The isnumber() function behaves similarly to isdigit(), but may recognize
     additional characters, depending on the current locale setting.

     The value of the argument must be representable as an unsigned char or
     the value of EOF.

RETURN VALUES
     The isdigit() and isnumber() functions return zero if the character tests
     false and return non-zero if the character tests true.
	 */

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}
