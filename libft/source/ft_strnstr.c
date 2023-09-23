/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:15:45 by ivanderw          #+#    #+#             */
/*   Updated: 2023/03/21 19:04:58 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
NAME
     strstr, strcasestr, strnstr -- locate a substring in a string

SYNOPSIS
     #include <string.h>

     char *
     strnstr(const char *haystack, const char *needle, size_t len);

DESCRIPTION
     The strstr() function locates the first occurrence of the null-terminated 
	 string needle in the null-terminated string haystack.

     The strnstr() function locates the first occurrence of the null-terminated 
	 string needle in the string haystack, where not more than len characters 
	 are searched.  Characters that appear after a `\0' character are not 
	 searched. Since the strnstr() function is a FreeBSD specific API, it 
	 should only be used when portability is not a concern.

RETURN VALUES
     If needle is an empty string, haystack is returned; if needle occurs 
	 nowhere in haystack, NULL is returned; otherwise a pointer to the first 
	 character of the first occurrence of needle is returned.

EXAMPLES
     The following sets the pointer ptr to the "Bar Baz" portion of largestring:

           const char *largestring = "Foo Bar Baz";
           const char *smallstring = "Bar";
           char *ptr;

           ptr = strstr(largestring, smallstring);

     The following sets the pointer ptr to NULL, because only the first 4 
	 characters 
	 of largestring are searched:

           const char *largestring = "Foo Bar Baz";
           const char *smallstring = "Bar";
           char *ptr;

           ptr = strnstr(largestring, smallstring, 4);
*/
#include <string.h>

static size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}	
	return (i);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	int		temp_counter;

	if (ft_strlen(needle) == 0)
		return ((char *)haystack);
	i = 0;
	while (haystack[i] != '\0' && i < len)
	{	
		if (haystack[i] == needle[0])
		{
			temp_counter = 0;
			while (temp_counter < (int)ft_strlen(needle))
			{
				if ((i + temp_counter) >= len)
					return ((void *) 0);
				if (haystack[(i + temp_counter)] != needle[temp_counter])
					break ;
				temp_counter++;
				if (temp_counter == (int)ft_strlen(needle))
					return ((char *)&haystack[i]);
			}
		}
		i++;
	}
	return ((void *) 0);
}
