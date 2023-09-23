/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 17:23:02 by ivanderw          #+#    #+#             */
/*   Updated: 2023/03/20 15:02:12 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
PROTOTYPE
	char *ft_itoa(int n);

PARAMETERS
	n: the integer to convert

RETURN VALUE
	The string representing the integer
	NULL if the allocation fails.

EXTERNAL FUNCTIONS
	malloc

DESCRIPTION
	Allocates (with malloc(3) and returns a string representing the integer
	received as an argument. Negative numbers must be handled.
*/
#include "libft.h"

size_t	get_int_length(int n)
{
	size_t	out;

	if (n == 0)
		return (1);
	out = 0;
	if (n < 0)
		out += 1;
	while (n != 0)
	{
		n = n / 10;
		out ++;
	}
	return (out);
}

char	*ft_itoa(int n)
{
	char	*output;
	size_t	length;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	else if (n == 0)
		return (ft_strdup("0"));
	length = get_int_length(n);
	output = (char *)malloc(sizeof(char) * length + 1);
	if (!output)
		return (NULL);
	if (n < 0)
	{
		output[0] = '-';
		n = -n;
	}
	output[length] = '\0';
	while (n != 0)
	{
		output[length - 1] = (n % 10) + '0';
		n = n / 10;
		length--;
	}
	return (output);
}

/*
 RECURSIVE IMPLEMENTATION (USES FREE IN HELPER FUNCTIONS)
static char	*ft_itoa_n_neg(int n)
{
	char	*output;
	char	*temp1;

	temp1 = ft_itoa(-n);
	if (!temp1)
		return (NULL);
	output = ft_strjoin("-", temp1);
	free(temp1);
	return (output);
}

static char	*ft_itoa_n_ten(int n)
{	
	char	*output;
	char	*temp1;
	char	*temp2;

	temp1 = ft_itoa(n / 10);
	temp2 = ft_itoa(n % 10);
	if (!temp1 || !temp2)
	{
		free(temp1);
		free(temp2);
		return (NULL);
	}
	output = ft_strjoin(temp1, temp2);
	free(temp1);
	free(temp2);
	return (output);
}

char	*ft_itoa(int n)
{
	char		*output;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	else if (n == 2147483647)
		return (ft_strdup("2147483647"));
	else if (n == 0)
		return (ft_strdup("0"));
	else if (n < 0)
		output = ft_itoa_n_neg(n);
	else if (n >= 10)
		output = ft_itoa_n_ten(n);
	else
	{
		output = malloc(2);
		if (!output)
			return (NULL);
		output[0] = n + '0';
		output[1] = '\0';
	}
	return (output);
}
*/
