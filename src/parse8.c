/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse8.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lxu <lxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:13:50 by lxu               #+#    #+#             */
/*   Updated: 2023/10/10 17:22:08 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	map_has_only_one_start_location(t_parsed_data *d)
{
	int		start_seen;
	size_t	i;
	size_t	j;

	start_seen = 0;
	if (!d->map)
		return (0);
	i = 0;
	while (d->map[i])
	{
		j = 0;
		while (d->map[i][j])
		{
			if (d->map[i][j] == 'N' || d->map[i][j] == 'E' || \
				d->map[i][j] == 'W' || d->map[i][j] == 'S')
				start_seen++;
			j++;
		}
		i++;
	}
	if (start_seen == 1)
		return (1);
	return (0);
}

t_coord	get_start_location(t_parsed_data *d)
{
	t_coord	res;
	size_t	i;
	size_t	j;

	res.x = -1;
	res.y = -1;
	if (!d->map)
		return (res);
	i = 0;
	while (d->map[i])
	{
		j = 0;
		while (d->map[i][j])
		{
			if (d->map[i][j] == 'N' || d->map[i][j] == 'E' || \
				d->map[i][j] == 'W' || d->map[i][j] == 'S')
			{
				return (res.x = j, res.y = i, res);
			}
			j++;
		}
		i++;
	}
	return (res);
}

char	**duplicate_map(char **map)
{
	char	**dup;
	size_t	height;
	size_t	i;
	char	*line;

	height = arr_len(map);
	dup = malloc(sizeof (*map) * (height + 1));
	if (!dup)
		return (NULL);
	dup[height] = NULL;
	i = 0;
	while (map[i])
	{
		line = ft_strdup(map[i]);
		if (!line)
			return (free_char_array(dup), NULL);
		dup[i] = line;
		if (!dup[i])
			return (free_char_array(dup), NULL);
		i++;
	}
	return (dup);
}

int	is_valid_by_flood_fill(char **map, int x, int y)
{
	if (x < 0 || y < 0)
		return (0);
	if (y >= (int)arr_len(map))
		return (0);
	if (x >= (int)ft_strlen(map[y]))
		return (0);
	if (map[y][x] == '0' || map[y][x] == 'N' || map[y][x] == 'S' \
		|| map[y][x] == 'W' || map[y][x] == 'E')
	{
		map[y][x] = 'x';
		if (is_valid_by_flood_fill(map, x - 1, y) == 0 || \
		is_valid_by_flood_fill(map, x + 1, y) == 0 || \
		is_valid_by_flood_fill(map, x, y - 1) == 0 || \
		is_valid_by_flood_fill(map, x, y + 1) == 0)
		{
			return (0);
		}
	}
	return (1);
}

int	is_enclosed_map(t_parsed_data *d)
{
	char	**dup;
	t_coord	start;
	int		res;

	if (!d)
	{
		return (0);
	}
	dup = duplicate_map(d->map);
	start = get_start_location(d);
	if (!dup || start.x < 0 || start.y < 0)
	{
		return (0);
	}
	res = is_valid_by_flood_fill(dup, start.x, start.y);
	free_char_array(dup);
	return (res);
}
