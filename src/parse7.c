/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lxu <lxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:13:50 by lxu               #+#    #+#             */
/*   Updated: 2023/10/07 19:23:51 by lxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

size_t	get_max_map_width(t_parsed_data *d)
{
	size_t	max_width;
	size_t	i;

	if (!d->map)
	{
		return (0);
	}
	max_width = 0;
	i = 0;
	while (d->map[i])
	{
		if (ft_strlen(d->map[i]) > max_width)
		{
			max_width = ft_strlen(d->map[i]);
		}
		i++;
	}
	return (max_width);
}

void	replace_map_spaces_with_zeros(t_parsed_data *d)
{
	size_t	i;
	size_t	j;

	if (!d->map)
	{
		return ;
	}
	i = 0;
	while (d->map[i])
	{
		j = 0;
		while (d->map[i][j])
		{
			if (d->map[i][j] == ' ')
			{
				d->map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
}

char	*extend_map_line(char *line, size_t new_width)
{
	char	*new_line;
	size_t	i;

	if (new_width <= ft_strlen(line))
		return (line);
	new_line = malloc(sizeof (*line) * (new_width + 1));
	if (!new_line)
		return (free(line), NULL);
	i = 0;
	while (line[i])
	{
		new_line[i] = line[i];
		i++;
	}
	while (i < new_width)
	{
		new_line[i] = '0';
		i++;
	}
	new_line[i] = '\0';
	free(line);
	return (new_line);
}

void	extend_map_lines_to_rectangle(t_parsed_data *d)
{
	size_t	max_width;
	size_t	i;

	if (!d->map)
	{
		return ;
	}
	max_width = get_max_map_width(d);
	i = 0;
	while (d->map[i])
	{
		d->map[i] = extend_map_line(d->map[i], max_width);
		i++;
	}
}
