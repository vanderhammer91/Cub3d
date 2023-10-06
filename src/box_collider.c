/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box_collider.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 14:27:34 by ivanderw          #+#    #+#             */
/*   Updated: 2023/10/06 10:35:35 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "box_collider.h"

void	c3d_collider_check_all(t_game *game)
{	
	t_ray	this_ray;
	int 	has_set;
	int	j;
	int	i;
	float	pt_dist;
	t_point *point;

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
		{	
			point = NULL;
			point = ray_cast(game->walls[j], &this_ray);
			if (point && game->walls[j]->direction != DOOR)
			{
				pt_dist = -1;
				pt_dist = get_raylength(this_ray, *point);
				if (pt_dist != -1 && pt_dist < 15)
				{
					has_set = 1;
				}
			}
			else if (point && game->walls[j]->direction == DOOR)
			{
				if (game->walls[j]->is_active)
				{
					pt_dist = -1;
					pt_dist = get_raylength(this_ray, *point);
					if (pt_dist != -1 && pt_dist < 15)
					{
						has_set = 1;
					}
				}
			}
			else
			{}
			if (point)
				free(point);
			j++;
		}
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
		i++;
	}		
}


int	c3d_collider_feedback(t_game *game)
{
	t_point start;
	t_point end;
	t_vector unitVector;
	double radius = 15;
	double radians;
	int i = 0;
	while (i < 4)
	{
		radians = i * (M_PI / 2);
		start.x = 150;
		start.y = 150;
		unitVector.x = cos(radians) * radius;
		unitVector.y = sin(radians) * radius;
		end.x = start.x + unitVector.x;
		end.y = start.y + unitVector.y;
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

void	test_hitrays(t_game *game)
{
	c3d_collider_check_all(game);
//	c3d_collider_feedback(game);
}
