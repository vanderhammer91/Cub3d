/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 17:00:39 by ivanderw          #+#    #+#             */
/*   Updated: 2023/03/18 17:07:26 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
PROTOTYPE
	void ft_putendl_fd(char *s, int fd);

PARAMETERS
	s: The string to output.
	fd: The file descriptor on which to write.

EXTERNAL FUNCTIONS
	Write

DESCRIPTION
	Outputs the string 's' to the given file descriptor followed by a newline.
*/
#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
	ft_putchar_fd('\n', fd);
}
