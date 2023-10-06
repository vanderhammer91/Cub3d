/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box_collider.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 14:27:34 by ivanderw          #+#    #+#             */
/*   Updated: 2023/10/06 13:54:49 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "box_collider.h"

void	c3d_collider_check_all_do1(t_bound *this_wall,
		t_ray *this_ray, int *has_set)
{
	t_point	*point;
	float	pt_dist;

	point = NULL;
	point = ray_cast(this_wall, this_ray);
	if (point && this_wall->type != DOOR)
	{
		pt_dist = -1;
		pt_dist = get_raylength(*this_ray, *point);
		if (pt_dist != -1 && pt_dist < 15)
			*has_set = 1;
	}
	else if (point && this_wall->type == DOOR)
	{
		if (this_wall->is_active)
		{
			pt_dist = -1;
			pt_dist = get_raylength(*this_ray, *point);
			if (pt_dist != -1 && pt_dist < 15)
				*has_set = 1;
		}
	}
	if (point)
		free(point);
}

void	c3d_set_bumpers(t_game *game, t_ray this_ray, int has_set)
{
	if (has_set)
	{
		if (this_ray.rot == 0)
			game->player.rb = 1;
		else if (this_ray.rot == 90)
			game->player.ub = 1;
		else if (this_ray.rot == 180)
			game->player.lb = 1;
		else if (this_ray.rot == 270)
			game->player.db = 1;
	}
	else
	{
		if (this_ray.rot == 0)
			game->player.rb = 0;
		else if (this_ray.rot == 90)
			game->player.ub = 0;
		else if (this_ray.rot == 180)
			game->player.lb = 0;
		else if (this_ray.rot == 270)
			game->player.db = 0;
	}
}

void	c3d_collider_check_all(t_game *game)
{
	t_ray	this_ray;
	int		has_set;
	int		i;
	int		j;

	this_ray.pos.x = game->player.pos.x;
	this_ray.pos.y = game->player.pos.y;
	this_ray.rot = 0;
	i = 0;
	while (i < 4)
	{
		this_ray.rot = i * 90;
		has_set = 0;
		j = 0;
		while (game->walls[j])
			c3d_collider_check_all_do1(game->walls[j++], &this_ray, &has_set);
		c3d_set_bumpers(game, this_ray, has_set);
		i++;
	}
}

/*
 * Unused feedback function that shows which colliders have 
 * been triggered visually on the minimap.
int	c3d_collider_feedback(t_game *game)
{
	t_point		start;
	t_point		end;
	double		radius;
	double		radians;
	int			i;

	radius = 15;
	i = 0;
	while (i < 4)
	{
		radians = i * (M_PI / 2);
		start.x = 150;
		start.y = 150;
		end.x = start.x + cos(radians) * radius;
		end.y = start.y + sin(radians) * radius;
		if (i == 0)
		{
			if (game->player.rb == 1)
				line(game->img, start, end, 0xFFFFFF);
			else
				line(game->img, start, end, 0xFFFF00);
		}
		if (i == 1)
		{
			if (game->player.ub == 1)
				line(game->img, start, end, 0xFFFFFF);
			else
				line(game->img, start, end, 0xFFFF00);
		}
		if (i == 2)
		{
			if (game->player.lb == 1)
				line(game->img, start, end, 0xFFFFFF);
			else
				line(game->img, start, end, 0xFFFF00);
		}
		if (i == 3)
		{
			if (game->player.db == 1)
				line(game->img, start, end, 0xFFFFFF);
			else
				line(game->img, start, end, 0xFFFF00);
		}
		i++;
	}
	return (0);
}
*/

void	test_hitrays(t_game *game)
{
	c3d_collider_check_all(game);
}
//	c3d_collider_feedback(game);
