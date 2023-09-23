/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 13:09:20 by ivanderw          #+#    #+#             */
/*   Updated: 2023/03/08 13:45:34 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
 *  #include <ctype.h>

     int
     isalpha(int c);

DESCRIPTION
     The isalpha() function tests for any character for which isupper(3) or
     islower(3) is true.  The value of the argument must be representable as 
	 an
     unsigned char or the value of EOF.

RETURN VALUES
     The isalpha() function returns zero if the character tests false and 
	 returns non-zero if the character tests true.

COMPATIBILITY
     The 4.4BSD extension of accepting arguments outside of the range of the
     unsigned char type in locales with large character sets is considered 
	 obsolete
     and may not be supported in future releases.  The iswalpha() function 
	 should be used instead.

SEE ALSO
     ctype(3), isalnum_l(3), islower(3), isupper(3), iswalpha(3), ascii(7)

STANDARDS
     The isalpha() function conforms to ISO/IEC 9899:1990 (``ISO C90'').
*/

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	else
		return (0);
}
