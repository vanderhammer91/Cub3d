/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lxu <lxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:23:16 by ivanderw          #+#    #+#             */
/*   Updated: 2023/10/09 18:26:39 by lxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "initialize.h"

void	c3d_add_northbound(t_game *game, int i, int j)
{
	t_bvertices bv;	

	bv.s_x = j * 64;
	bv.s_y = (i + 1) * 64;
	bv.e_x = (j + 1) * 64;
	bv.e_y = (i + 1) * 64;
	add_bound(game, bv, NORTH);	
}

void	c3d_add_eastbound(t_game *game, int i, int j)
{
	t_bvertices bv;	

	bv.s_x = (j + 1) * 64;
	bv.s_y = (i + 1) * 64;
	bv.e_x = (j + 1) * 64;
	bv.e_y = i * 64;
	add_bound(game, bv, EAST);	
}

void	c3d_add_southbound(t_game *game, int i, int j)
{
	t_bvertices bv;	

	bv.s_x = (j + 1) * 64;
	bv.s_y = i * 64;
	bv.e_x = j * 64;
	bv.e_y = i * 64;
	add_bound(game, bv, SOUTH);
}

void	c3d_add_westbound(t_game *game, int i, int j)
{
	t_bvertices bv;	

	bv.s_x = j * 64;
	bv.s_y = i * 64;
	bv.e_x = j * 64;
	bv.e_y = (i + 1) * 64;
	add_bound(game, bv, WEST);	
}

void	c3d_add_doors_and_exits(t_game *game, int i, int j)
{
	t_bvertices bv;	

	if (game->raw[i][j-1] == '1' && game->raw[i][j + 1] == '1')
	{
		bv.s_x = j * 64;
		bv.s_y = (i + 0.5) * 64;
		bv.e_x = (j + 1) * 64;
		bv.e_y = (i + 0.5) * 64;
		if (game->raw[i][j] == '2')
			add_bound(game, bv, DOOR);	
		else
			add_bound(game, bv, EXIT);	
	}
	else if (game->raw[i - 1][j] == '1' && game->raw[i + 1][j] == '1')
	{
		bv.s_x = (j + 0.5) * 64;
		bv.s_y = i * 64;
		bv.e_x = (j + 0.5) * 64;
		bv.e_y = (i + 1) * 64;
		if (game->raw[i][j] == '2')
			add_bound(game, bv, DOOR);	
		else
			add_bound(game, bv, EXIT);
	}
}

void	c3d_add_ad(t_game *game, int i, int j)
{
	t_bvertices bv;	

	bv.s_x = (j - 2) * 64;
	bv.s_y = (i + 0.1) * 64;
	bv.e_x = (j + 1) * 64;
	bv.e_y = (i + 0.1) * 64;
	add_bound(game, bv, AD);
}

void	c3d_add_pillar(t_game *game, int i, int j)
{
	t_bvertices bv;	

	bv.s_x = ((j + 1) * 64) - 25 ;
	bv.s_y = ((i) * 64) + 25;
	bv.e_x = ((j) * 64) + 25;
	bv.e_y = ((i) * 64) + 25;
	add_bound(game, bv, SOUTH);
	bv.s_x = ((j) * 64) + 25;
	bv.s_y = ((i) * 64) + 25;
	bv.e_x = ((j) * 64) + 25;
	bv.e_y = ((i + 1) * 64) - 25;
	add_bound(game, bv, EAST);
	bv.s_x = ((j) * 64) + 25;
	bv.s_y = ((i + 1) * 64) - 25;
	bv.e_x = ((j + 1) * 64) - 25;
	bv.e_y = ((i + 1) * 64) - 25;
	add_bound(game, bv, NORTH);
	bv.s_x = ((j + 1) * 64) - 25;
	bv.s_y = ((i + 1) * 64) - 25;
	bv.e_x = ((j + 1) * 64) - 25;
	bv.e_y = ((i) * 64) + 25;
	add_bound(game, bv, WEST);
}

//void	c3d_set_wall_bounds_init(t_game *game, int *i, int *texture_width, int *count


int	c3d_set_wall_bounds(t_game *game)
{
	int	i;
	int	j;
	int	texture_width;
//	t_bvertices bv;

	i = 0;
	texture_width = 64;
	game->walls = malloc(sizeof(t_bound) * 250);
	if (!game->walls)
	{
		printf("c3d_set_wall_bounds: failed to malloc\n");
		return (1);
	}
	game->num_walls = 0;
	game->map_height = get_mapheight(game);
	game->map_width = ft_strlen(game->raw[i]) - 1;
	game->walls = malloc_bounds(game);
	while (i < game->map_height)
	{
		j = 0;
		while (j <= game->map_width)
		{
			if (game->raw[i][j] == '1')
			{
				if ((i - 1) > -1 && (is_space_char(game->raw[i - 1][j]) || is_player_char(game->raw[i - 1][j])))
					c3d_add_southbound(game, i, j);
				if ((j + 1) < game->map_width-1 && (is_space_char(game->raw[i][j + 1]) || is_player_char(game->raw[i][j + 1])))	
					c3d_add_eastbound(game, i, j);
				if ((i + 1) < game->map_height && (is_space_char(game->raw[i + 1][j]) || is_player_char(game->raw[i + 1][j])))
					c3d_add_northbound(game, i, j);				
				if ((j - 1) > -1 && (is_space_char(game->raw[i][j - 1]) || is_player_char(game->raw[i][j - 1])))
					c3d_add_westbound(game, i, j);
			}
			else if (game->raw[i][j] == '2' || game->raw[i][j] == '4')
				c3d_add_doors_and_exits(game, i, j);
			else if (game->raw[i][j] == '5')
				c3d_add_ad(game, i, j);
			else if (game->raw[i][j] == 'X')
				c3d_add_pillar(game, i, j);
			j++;
		}	
		i++;	
	}
	return (0);
}
