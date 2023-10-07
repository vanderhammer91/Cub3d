/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:09:20 by ivanderw          #+#    #+#             */
/*   Updated: 2023/10/07 17:26:56 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

void	c3d_player_cast_init(t_game *game, t_cast *pc, int i)
{
	pc->has_collided = 0;
	pc->max_dist = 100000;
	pc->second_max_dist = 100000;
	pc->this_ray.pos.x = game->player.pos.x;
	pc->this_ray.pos.y = game->player.pos.y;
	pc->this_ray.rot = get_safe_angle(game->player.rot + i * 0.25 - 35);
	pc->closest.x = -1;
	pc->closest.y = -1;
	pc->second_closest.x = -1;
	pc->second_closest.y = -1;
}

void	c3d_player_set(t_game *game, t_cast *pc, int j)
{
	t_point	*point;

	point = ray_cast(game->walls[j], &pc->this_ray);
	if (point)
	{
		pc->has_collided = 1;
		pc->pt_dist = get_raylength(pc->this_ray, *point);
		if (pc->pt_dist != -1 && pc->pt_dist < pc->max_dist)
		{
			pc->second_max_dist = pc->max_dist;
			pc->second_closest = pc->closest;
			pc->second_closest_wall = pc->closest_wall;
			pc->max_dist = pc->pt_dist;
			pc->closest = *point;
			pc->closest_wall = game->walls[j];
			game->cwi = j;
		}
		else if (pc->pt_dist != -1 && pc->pt_dist < pc->second_max_dist)
		{
			pc->second_max_dist = pc->pt_dist;
			pc->second_closest = *point;
			pc->second_closest_wall = game->walls[j];
		}
		free(point);
	}
}

void	c3d_player_cast_projection(t_game *game, t_cast pc, int i)
{
	if (pc.closest_wall->type == DOOR || pc.closest_wall->type == AD)
		c3d_draw_projection(game, pc.second_pt_dist, i, pc.second_closest.x, \
			pc.second_closest.y, pc.second_closest_wall);
	c3d_draw_projection(game, pc.pt_dist, i, pc.closest.x, pc.closest.y, \
			pc.closest_wall);
}

void	c3d_player_cast_help(t_game *game, t_cast pc)
{
	game->closest_wall_dir = pc.closest_wall->type;
	game->pt_dist = pc.pt_dist;
}

void	c3d_player_cast(t_game *game)
{
	t_cast	pc;

	pc.i = 0;
	while (pc.i < 280)
	{
		c3d_player_cast_init(game, &pc, pc.i);
		pc.j = 0;
		while (game->walls[pc.j])
			c3d_player_set(game, &pc, pc.j++);
		pc.ray_angle = fabs(pc.this_ray.rot - game->player.rot) * M_PI / 180.0;
		pc.pt_dist = (200 / (get_raylength(pc.this_ray, pc.closest) \
			* cos(pc.ray_angle))) * 200;
		if (pc.pt_dist > 3000)
			pc.pt_dist = 3000;
		if (pc.this_ray.rot == game->player.rot)
			c3d_player_cast_help(game, pc);
		pc.second_pt_dist = (200 / (get_raylength(pc.this_ray, \
			pc.second_closest) * cos(pc.ray_angle))) * 200;
		if (pc.second_pt_dist > 3000)
			pc.second_pt_dist = 3000;
		if (pc.has_collided)
			c3d_player_cast_projection(game, pc, pc.i);
		pc.i++;
	}
}
