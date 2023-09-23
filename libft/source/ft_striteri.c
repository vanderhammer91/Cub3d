/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 20:23:25 by ivanderw          #+#    #+#             */
/*   Updated: 2023/03/18 20:36:21 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
PROTOTYPE
	void ft_striteri(char *s, void (*f)(unsigned int, char*));

PARAMETERS
	s:	The string on which to iterate
	f:	The function to apply each character.

Applies the function 'f' on each character of the string passed as argument, 
passing its index as first argument. Each character is passed by address to 
’f’ to be modified if necessary.
*/
#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	if (!s || !f)
		return ;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
}
