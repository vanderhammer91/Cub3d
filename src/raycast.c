/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:09:20 by ivanderw          #+#    #+#             */
/*   Updated: 2023/09/25 19:57:37 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"
#include "frame_refresh.h"

extern int All_Textures[];

t_point *ray_cast(t_bound *current_wall, t_ray *this_ray)
{
//	t_point *ret;
	t_point *pt;
	double radians = this_ray->rot * M_PI / 180.0;
	
	float x1 = current_wall->start.x;	
	float y1 = current_wall->start.y;	
	float x2 = current_wall->end.x;	
	float y2 = current_wall->end.y;	

	float x3 = this_ray->pos.x;
	float y3 = this_ray->pos.y;
	float x4 = this_ray->pos.x + cos(radians);
	float y4 = this_ray->pos.y + sin(radians);
		
	float denominator = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
	if (denominator != 0)
	{
		float t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / denominator;
		float u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / denominator;
	if (t > 0 && t < 1 && u > 0)
	{
        	pt = malloc(sizeof(t_point));
		if (!pt)
		{
			printf("c3d_internal: raycast: failed malloc\n");
			return (NULL);
		}
        	pt->x = x1 + t * (x2 - x1);
        	pt->y = y1 + t * (y2 - y1);
        	return pt;
      	}
	else 
	{  
	 	return NULL;
	}
	}
	else
	{
		return NULL;
	}	
}

float	get_raylength(t_ray ray, t_point end)
{
	float	x_diff;
	float	y_diff;

	x_diff = end.x - ray.pos.x;
	y_diff = end.y - ray.pos.y;

	return (sqrt(x_diff * x_diff + y_diff * y_diff));
}

void	c3d_draw_projection(t_game *game, float raylength, int i, int ray_x, int ray_y, t_bound *closest_wall)
{
	int colour;
	int	y; 
	int		start_y;
	float	ty;
	float	ty_step;
	float	tx;
	float	c;

	if (closest_wall->direction == EAST)
		colour = 0x00FFFF;
	else if (closest_wall->direction == WEST)
		colour = 0x0000FF;			
	else if (closest_wall->direction == SOUTH)
		colour = 0x00FF00;
	else if (closest_wall->direction == NORTH)
		colour = 0xFF0000;	
	else
		colour = 0x000000;

	y = 0;
	if (closest_wall->direction == NORTH || closest_wall->direction == SOUTH)
	{
		start_y = 400 - raylength * 0.5;
		ty =  closest_wall->direction * 32;
		ty_step = 32.0 / (float)raylength;
		tx = (int)(ray_x/2.0) % 32;
		if (closest_wall->direction == NORTH)
			tx = 31 - tx;
		while (y < raylength)
		{
			c = All_Textures[(int)(ty) * 32 + (int)(tx)];	
			rect(game->img, 800 + i * 6, start_y + y, 6, 1, colour * c);
			ty += ty_step;
			y++;
		}
	}
	else if (closest_wall->direction == EAST || closest_wall->direction == WEST)
	{
		start_y = 400 - raylength * 0.5;
		ty =  closest_wall->direction * 32;
		ty_step = 32.0 / (float)raylength;
		tx = (int)(ray_y/2.0) % 32;
		if (closest_wall->direction == EAST)
			tx = 31 - tx;
		while (y < raylength)
		{
			c = All_Textures[(int)(ty) * 32 + (int)(tx)];	
			rect(game->img, 800 + i * 6, start_y + y, 6, 1, colour * c);
			ty += ty_step;
			y++;
		}
	}
//	else
//		rect(game->img, 800 + i * 6, (400 - raylength * 0.5), 6, raylength, colour);
}

void	c3d_player_look(t_game *game)
{
	t_ray	this_ray;
  	t_point closest;
	t_point *point;
//	t_bound	*current_wall;
	t_bound	*closest_wall;
	float	pt_dist;
	double	ray_angle;
	int	has_collided;
	float	max_dist;
	int i = 0;
	int j;
	while (i < 140)
	{
		has_collided = 0;	
		max_dist = 100000;
		this_ray.pos.x = game->player.pos.x;
		this_ray.pos.y = game->player.pos.y;
		this_ray.rot = get_safe_angle(game->player.rot + i*0.5 -35);
		closest.x = -1;
		closest.y = -1;
	//	current_wall = *game->walls;
    	//while (current_wall != NULL)
    //	{
	j = 0;
	while (game->walls[j])
	{	
		point = NULL;
    	  	point = ray_cast(game->walls[j], &this_ray);
			if (point)
			{
				has_collided = 1;
				pt_dist = -1;
				pt_dist = get_raylength(this_ray, *point);
				if (pt_dist != -1 && pt_dist < max_dist)
				{
					max_dist = pt_dist;
					closest = *point;
					closest_wall = game->walls[j];
				}
				free(point);
			}
			else
			{
			}
			j++;
		}
		//	line(game->img, this_ray.pos, closest, 0x00FF00);
			ray_angle = fabs(this_ray.rot - game->player.rot) * M_PI / 180.0;
			pt_dist = (200 / (get_raylength(this_ray, closest)* cos(ray_angle))) * 200; 
			if (has_collided)
				c3d_draw_projection(game, pt_dist, i, closest.x, closest.y, closest_wall);
			i++;
	}
}

