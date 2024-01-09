/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 19:55:34 by ivanderw          #+#    #+#             */
/*   Updated: 2023/10/10 17:38:41 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "initialize.h"

void	c3d_add_southbound(t_game *game, int i, int j)
{
	t_bvertices	bv;	

	bv.s_x = (j + 1) * 64;
	bv.s_y = i * 64;
	bv.e_x = j * 64;
	bv.e_y = i * 64;
	add_bound(game, bv, SOUTH);
}

void	c3d_add_eastbound(t_game *game, int i, int j)
{
	t_bvertices	bv;	

	bv.s_x = j * 64;
	bv.s_y = i * 64;
	bv.e_x = j * 64;
	bv.e_y = (i + 1) * 64;
	add_bound(game, bv, EAST);
}

void	c3d_add_doors_and_exits(t_game *game, int i, int j)
{
	t_bvertices	bv;

	if (game->raw[i][j - 1] == '1' && game->raw[i][j + 1] == '1')
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

void	c3d_add_pillar(t_game *game, int i, int j)
{
	t_bvertices	bv;	

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
