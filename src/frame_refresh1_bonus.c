/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_refresh1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:07:44 by ivanderw          #+#    #+#             */
/*   Updated: 2023/10/10 15:05:27 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frame_refresh.h"

double	get_safe_angle(double angle)
{
	while (angle < 0)
		angle += 360;
	while (angle > 360)
		angle -= 360;
	return (angle);
}

void	set_point(t_point *point, int x, int y)
{
	point->x = x;
	point->y = y;
}

int	draw_dir_arrow(t_game *game)
{
	t_point		start;
	t_point		end;
	t_point		unit_vector;
	double		radians;
	double		radius;

	radians = game->player.rot * M_PI / 180.0;
	radius = 15;
	start.x = 150;
	start.y = 150;
	unit_vector.x = cos(radians) * radius;
	unit_vector.y = sin(radians) * radius;
	end.x = start.x + unit_vector.x;
	end.y = start.y + unit_vector.y;
	line(game->img, start, end, 0x00FFFF);
	return (0);
}

void	c3d_draw_overlay(t_game *game)
{
	if (game->pt_dist > 700)
	{
		if (game->closest_wall_dir == DOOR)
		{
			mlx_put_image_to_window(game->mlx, game->mlx_win,
				game->t_lib.e_texture, 100, 900);
			if (game->keys.e_key_down == 1)
			{
				if (game->walls[game->cwi]->door_state == 0)
				{
					game->walls[game->cwi]->door_state = 1;
				}
				else if (game->walls[game->cwi]->door_state == 10)
				{
					game->walls[game->cwi]->door_state = 11;
				}
			}
		}
	}
	if (game->pt_dist > 1200 && game->closest_wall_dir == EXIT)
	{
		game->game_state = 2;
	}
}
