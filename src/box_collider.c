/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box_collider.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 14:27:34 by ivanderw          #+#    #+#             */
/*   Updated: 2023/09/22 20:55:42 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "box_collider.h"

int	test_right_hitray(t_game *game)
{
	t_point start;
	t_point end;
	t_vector unitVector;
	double radians = 0;
	double radius = 15;

	start.x = game->player.pos.x;
	start.y = game->player.pos.y;

	//green line in the direction the player is facing.
	unitVector.x = cos(radians) * radius;
	unitVector.y = sin(radians) * radius;
	end.x = start.x + unitVector.x;
	end.y = start.y + unitVector.y;
	c3d_collider_check_right(game);
	if (game->player.rb == 1)
		line(game->img, start, end, 0xFFFFFF);
	else
		line(game->img, start, end, 0xFFFF00);

	return (0);
}

void	c3d_collider_check_right(t_game *game)
{	
	t_ray	this_ray;
	int 	has_set;
	int	j;
	float	pt_dist;
	t_point *point;

	this_ray.pos.x = game->player.pos.x;
	this_ray.pos.y = game->player.pos.y;
	this_ray.rot = 0;
	has_set = 0;
	j = 0;
	while (game->walls[j])
	{	
		point = NULL;
		point = ray_cast(game->walls[j], &this_ray);
		if (point)
		{
			pt_dist = -1;
			pt_dist = get_raylength(this_ray, *point);
			if (pt_dist != -1 && pt_dist < 15)
			{
				has_set = 1;
			}
			free(point);
		}
		else
		{
		}
		j++;
	}
	if (has_set)
		game->player.rb = 1;
	else
		game->player.rb = 0;
}

int	test_left_hitray(t_game *game)
{
	t_point start;
	t_point end;
	t_vector unitVector;
	double radians = M_PI;
	double radius = 15;

	start.x = game->player.pos.x;
	start.y = game->player.pos.y;

	//green line in the direction the player is facing.
	unitVector.x = cos(radians) * radius;
	unitVector.y = sin(radians) * radius;
	end.x = start.x + unitVector.x;
	end.y = start.y + unitVector.y;
	c3d_collider_check_left(game);
	if (game->player.lb == 1)
		line(game->img, start, end, 0xFFFFFF);
	else
		line(game->img, start, end, 0xFFFF00);

	return (0);
}

/*
void	c3d_collider_check_left(t_game *game)
{	
	t_ray	this_ray;
	int 	has_set;
	float	pt_dist;
	t_bound	*current_wall;
	t_point *point;

	this_ray.pos.x = game->player.pos.x;
	this_ray.pos.y = game->player.pos.y;
	this_ray.rot = 180;
	has_set = 0;

	current_wall = *game->walls;
    while (current_wall != NULL)
    {
		point = NULL;
		point = ray_cast(current_wall, &this_ray);
		if (point)
		{
			pt_dist = -1;
			pt_dist = get_raylength(this_ray, *point);
			if (pt_dist != -1 && pt_dist < 15)
			{
				has_set = 1;
			}
		}
		free(point);
		if (!current_wall->next)
			break;
		current_wall = current_wall->next;
	}
	if (has_set)
		game->player.lb = 1;
	else
		game->player.lb = 0;
}
*/
void	c3d_collider_check_left(t_game *game)
{	
	t_ray	this_ray;
	int 	has_set;
	int	j;
	float	pt_dist;
	t_point *point;

	this_ray.pos.x = game->player.pos.x;
	this_ray.pos.y = game->player.pos.y;
	this_ray.rot = 180;
	has_set = 0;
	j = 0;
	while (game->walls[j])
	{	
		point = NULL;
		point = ray_cast(game->walls[j], &this_ray);
		if (point)
		{
			pt_dist = -1;
			pt_dist = get_raylength(this_ray, *point);
			if (pt_dist != -1 && pt_dist < 15)
			{
				has_set = 1;
			}
			free(point);
		}
		else
		{
		}
		j++;
	}
	if (has_set)
		game->player.rb = 1;
	else
		game->player.rb = 0;
}



void	test_hitrays(t_game *game)
{
	test_right_hitray(game);
	test_left_hitray(game);
//	test_up_hitray(game);
//	test_down_hitray(game);
}
