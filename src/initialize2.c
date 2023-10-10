/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lxu <lxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:23:16 by ivanderw          #+#    #+#             */
/*   Updated: 2023/10/10 16:17:43 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "initialize.h"

void	c3d_add_northbound(t_game *game, int i, int j)
{
	t_bvertices	bv;	

	bv.s_x = j * 64;
	bv.s_y = (i + 1) * 64;
	bv.e_x = (j + 1) * 64;
	bv.e_y = (i + 1) * 64;
	add_bound(game, bv, NORTH);
}

void	c3d_add_westbound(t_game *game, int i, int j)
{
	t_bvertices	bv;	

	bv.s_x = (j + 1) * 64;
	bv.s_y = (i + 1) * 64;
	bv.e_x = (j + 1) * 64;
	bv.e_y = i * 64;
	add_bound(game, bv, WEST);
}

void	c3d_set_wall_bounds_init(t_game *game, int *i, int *texture_width)
{
	*i = 0;
	*texture_width = 64;
	game->num_walls = 0;
	game->map_height = get_mapheight(game);
	game->map_width = ft_strlen(game->raw[*i]) - 1;
	game->walls = malloc_bounds(game);
}

void	c3d_set_wall_bounds_do(t_game *game, int i, int j)
{
	if ((i - 1) > -1 && (is_space_char(game->raw[i - 1][j]) || \
				is_player_char(game->raw[i - 1][j])))
		c3d_add_southbound(game, i, j);
	if ((j + 1) < game->map_width - 1 && (is_space_char(game->raw[i][j + 1]) || \
				is_player_char(game->raw[i][j + 1])))
		c3d_add_westbound(game, i, j);
	if ((i + 1) < game->map_height && (is_space_char(game->raw[i + 1][j]) || \
				is_player_char(game->raw[i + 1][j])))
		c3d_add_northbound(game, i, j);
	if ((j - 1) > -1 && (is_space_char(game->raw[i][j - 1]) || \
				is_player_char(game->raw[i][j - 1])))
		c3d_add_eastbound(game, i, j);
}

int	c3d_set_wall_bounds(t_game *game)
{
	int	i;
	int	j;
	int	texture_width;

	c3d_set_wall_bounds_init(game, &i, &texture_width);
	while (i < game->map_height)
	{
		j = 0;
		while (j <= game->map_width)
		{
			if (game->raw[i][j] == '1')
				c3d_set_wall_bounds_do(game, i, j);
			j++;
		}
		i++;
	}
	return (0);
}
