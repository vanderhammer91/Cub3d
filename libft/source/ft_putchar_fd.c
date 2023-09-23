/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 16:34:20 by ivanderw          #+#    #+#             */
/*   Updated: 2023/03/18 17:09:45 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
PROTOTYPE
	void ft_putchar_fd(char c, int fd);

PARAMETERS
	c: 	The character to output.
	fd:	The file descriptor on which to write.

EXTERNAL FUNCTS.
	write

DESCRIPTION 
	Outputs the character 'c' to the given file descriptor.
*/
#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
