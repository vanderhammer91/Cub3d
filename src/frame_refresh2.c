/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_refresh2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:19:35 by ivanderw          #+#    #+#             */
/*   Updated: 2023/10/09 18:11:34 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frame_refresh.h"

void	c3d_update_player_pos_2(t_game *game, double *new_x, double *new_y,
		int format)
{
	double	radians;
	int		sign;

	if (format == 1 || format == 4)
	{
		sign = 1;
	}
	else
	{
		sign = -1;
	}
	if (format == 1 || format == 2)
	{
		radians = game->player.rot * M_PI / 180;
	}
	else
	{
		radians = get_safe_angle((game->player.rot + 90)) * (M_PI / 180);
	}
	*new_x = game->player.pos.x + sign * game->speed * cos(radians);
	*new_y = game->player.pos.y + sign * game->speed * sin(radians);
}

int	c3d_update_player_pos_1(t_game *game, double *new_x, double *new_y)
{
	int		has_set;

	has_set = 1;
	if (game->keys.U_KEY_DOWN && !game->keys.D_KEY_DOWN)
		c3d_update_player_pos_2(game, new_x, new_y, 1);
	else if (game->keys.D_KEY_DOWN && !game->keys.U_KEY_DOWN)
		c3d_update_player_pos_2(game, new_x, new_y, 2);
	else if (game->keys.L_KEY_DOWN && !game->keys.R_KEY_DOWN)
		c3d_update_player_pos_2(game, new_x, new_y, 3);
	else if (game->keys.R_KEY_DOWN && !game->keys.L_KEY_DOWN)
		c3d_update_player_pos_2(game, new_x, new_y, 4);
	else
		has_set = 0;
	return (has_set);
}

void	c3d_update_player_rot(t_game *game, double it)
{
	game->player.rot = game->player.rot + (it * game->speed);
	if (game->player.rot < 0)
		game->player.rot += 360;
	else if (game->player.rot > 360)
		game->player.rot -= 360;
}

int	c3d_update_player_pos(t_game *game)
{
	int		has_set;
	double	new_x;
	double	new_y;

	game->speed = 3;
	if (game->keys.SH_KEY_DOWN == 1)
		game->speed *= 2;
	has_set = c3d_update_player_pos_1(game, &new_x, &new_y);
	if (has_set)
	{
		if (new_x > game->player.pos.x && !game->player.rb)
			game->player.pos.x = new_x;
		if (new_x < game->player.pos.x && !game->player.lb)
			game->player.pos.x = new_x;
		if (new_y < game->player.pos.y && !game->player.db)
			game->player.pos.y = new_y;
		if (new_y > game->player.pos.y && !game->player.ub)
			game->player.pos.y = new_y;
	}
	if (game->keys.R_ROT_KEY_DOWN)
		c3d_update_player_rot(game, -0.5);
	else if (game->keys.L_ROT_KEY_DOWN)
		c3d_update_player_rot(game, 0.5);
	return (0);
}
