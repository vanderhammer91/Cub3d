/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lxu <lxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:21:34 by lxu               #+#    #+#             */
/*   Updated: 2023/10/09 20:06:40 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "initialize.h"

int	num_adjacent(t_game *game, char **map, int i, int j)
{
	int	adj;

	adj = 0;
	if (i - 1 > -1 && \
		(is_space_char(map[i - 1][j]) || is_player_char(map[i - 1][j])))
	{
		adj++;
	}
	if (j + 1 < game->map_width - 1 && \
		(is_space_char(map[i][j + 1]) || is_player_char(map[i][j + 1])))
	{
		adj++;
	}
	if (i + 1 < game->map_height && \
		(is_space_char(map[i + 1][j]) || is_player_char(map[i + 1][j])))
	{
		adj++;
	}
	if (j - 1 > -1 && \
		(is_space_char(map[i][j - 1]) || is_player_char(map[i][j - 1])))
	{
		adj++;
	}
	return (adj);
}

int	c3d_count_bounds(t_game *game)
{
	size_t	count;
	int		i;
	int		j;

	count = 0;
	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j <= game->map_width)
		{
			if (game->raw[i][j] == '1')
				count += num_adjacent(game, game->raw, i, j);
			else if (game->raw[i][j] == '2' || game->raw[i][j] == '4')
				count++;
			else if (game->raw[i][j] == '5')
				count++;
			else if (game->raw[i][j] == 'X')
				count += 4;
			j++;
		}
		i++;
	}
	return (count);
}

t_bound	**malloc_bounds(t_game *game)
{
	t_bound	**bounds_pointer;
	size_t	length;

	length = c3d_count_bounds(game);
	bounds_pointer = malloc(sizeof(*bounds_pointer) * length);
	if (!bounds_pointer)
	{
		return (NULL);
	}
	return (bounds_pointer);
}
