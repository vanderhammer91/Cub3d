/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_refresh2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:19:35 by ivanderw          #+#    #+#             */
/*   Updated: 2023/10/06 17:14:47 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frame_refresh.h"

int	c3d_update_player_pos_1(t_game *game, double *new_x, double *new_y, int speed)
{
	double	radians;
	double	perp_rad;
	int		has_set;

	radians = game->player.rot * M_PI / 180;
	perp_rad = get_safe_angle((game->player.rot + 90)) * (M_PI / 180);
	has_set = 0;
	if (game->keys.U_KEY_DOWN && !game->keys.D_KEY_DOWN)
	{
		*new_x = game->player.pos.x + speed * cos(radians);
		*new_y = game->player.pos.y + speed * sin(radians);
		has_set = 1;
	}
	else if (game->keys.D_KEY_DOWN && !game->keys.U_KEY_DOWN)
	{
		*new_x = game->player.pos.x - speed * cos(radians);
		*new_y = game->player.pos.y - speed * sin(radians);
		has_set = 1;
	}
	else if (game->keys.L_KEY_DOWN && !game->keys.R_KEY_DOWN)
	{
		*new_x = game->player.pos.x - speed * cos(perp_rad);
		*new_y = game->player.pos.y - speed * sin(perp_rad);
		has_set = 1;
	}
	else if (game->keys.R_KEY_DOWN && !game->keys.L_KEY_DOWN)
	{
		*new_x = game->player.pos.x + speed * cos(perp_rad);
		*new_y = game->player.pos.y + speed * sin(perp_rad);
		has_set = 1;
	}
	return (has_set);
}

void	c3d_update_player_rot(t_game *game, double it, int speed)
{
		game->player.rot = game->player.rot + (it * speed);	
		if (game->player.rot < 0)
			game->player.rot += 360;
}

int		c3d_update_player_pos(t_game *game)
{
	int	speed;
	double new_x;
	double new_y;
	int		has_set;

	speed = 3;
	if (game->keys.SH_KEY_DOWN == 1)
		speed *= 2;
	has_set = c3d_update_player_pos_1(game, &new_x, &new_y, speed);
	if(has_set)
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
		c3d_update_player_rot(game, -0.5, speed);
	else if (game->keys.L_ROT_KEY_DOWN)
		c3d_update_player_rot(game, 0.5, speed);
	return (0);
}

