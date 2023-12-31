/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lxu <lxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:13:50 by lxu               #+#    #+#             */
/*   Updated: 2023/10/09 11:52:15 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	is_valid_line_map(char *line)
{
	size_t	i;

	if (!line)
	{
		return (0);
	}
	i = 0;
	while (line[i])
	{
		if (line[i] == '0' || line[i] == '1' || line[i] == ' ' || \
			line[i] == 'X' || line[i] == '2' || line[i] == '4' || \
			line[i] == '5' || line[i] == 'N' || line[i] == 'S' || \
			line[i] == 'E' || line[i] == 'W')
		{
		}
		else
		{
			return (0);
		}
		i++;
	}
	return (1);
}
