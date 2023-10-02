/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:09:20 by ivanderw          #+#    #+#             */
/*   Updated: 2023/10/02 21:01:32 by ivanderw         ###   ########.fr       */
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
	}
	return NULL;
}

float	get_raylength(t_ray ray, t_point end)
{
	float	x_diff;
	float	y_diff;

	x_diff = end.x - ray.pos.x;
	y_diff = end.y - ray.pos.y;
	return (sqrt(x_diff * x_diff + y_diff * y_diff));
}

int retrieve_colour(void *img, int x, int y)
{
    char    *data;
    int     bpp;
    int     size_line;
    int     endian;
    int     colour;

    data = mlx_get_data_addr(img, &bpp, &size_line, &endian);
    colour = *(int *)(data + ((x * bpp / 8) + (y * size_line)));
    return (colour);
}

void	c3d_draw_projection(t_game *game, float raylength, int i, int ray_x, int ray_y, t_bound *closest_wall)
{
	int colour;
	int	y; 
	int		start_y;
	float	ty;
	float	ty_step;
	float	tx;
	int	x_offset = 0;
	int y_offset = 500;
	int	cw = 5;

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
 	if (closest_wall->direction == SOUTH)
	{
    	start_y = y_offset - raylength * 0.5;
    	ty = 0;
    	ty_step = 64.0 / (float)raylength;
		tx = (int)(ray_x) % 64;
		tx = 63 - tx;
    	while (y < raylength)
    	{
    	  	int pixel_colour = retrieve_colour(game->south_texture, tx, ty);
		   	rect(game->img, x_offset + i * cw, start_y + y, cw, 1, pixel_colour);
    	    ty += ty_step;
    	    y++;
    	}
	}
 	else if (closest_wall->direction == NORTH)
	{
    	start_y = y_offset - raylength * 0.5;
    	ty = 0;
    	ty_step = 64.0 / (float)raylength;
		tx = (int)(ray_x) % 64;
    	while (y < raylength)
    	{
    	 	int pixel_colour = retrieve_colour(game->north_texture, tx, ty);
    	 	rect(game->img, x_offset + i * cw, start_y + y, cw, 1, pixel_colour);
    	    ty += ty_step;
    	    y++;
    	}
	}
	else if (closest_wall->direction == EAST)
	{
    	start_y = y_offset - raylength * 0.5;
    	ty = 0;
    	ty_step = 64.0 / (float)raylength;
		tx = (int)(ray_y) % 64;
    	while (y < raylength)
    	{
    	  	int pixel_colour = retrieve_colour(game->east_texture, tx, ty);
		   	rect(game->img, x_offset + i * cw, start_y + y, cw, 1, pixel_colour);
    	    ty += ty_step;
    	    y++;
    	}
	}
 	else if (closest_wall->direction == WEST)
	{
    	start_y = y_offset - raylength * 0.5;
    	ty = 0;
    	ty_step = 64.0 / (float)raylength;
		tx = (int)(ray_y) % 64;
		tx = 63 - tx;
    	while (y < raylength)
    	{
    	 	int pixel_colour = retrieve_colour(game->west_texture, tx, ty);
			rect(game->img, x_offset + i * cw, start_y + y, cw, 1, pixel_colour);
    	    ty += ty_step;
    	    y++;
    	}
	}
 	else if (closest_wall->direction == DOOR)
	{
    	start_y = y_offset - raylength * 0.5;
    	ty = 0;
    	ty_step = 128.0 / (float)raylength;
		if (closest_wall->is_vert == 0)
    		tx = (int)(ray_x) % 128;
		else
    		tx = (int)(ray_y) % 128;
    	while (y < raylength)
    	{
    	 	int pixel_colour = retrieve_colour(game->door_texture, tx * 2,
					ty + game->true_state * 128);
			int alpha = (pixel_colour >> 24) & 0xFF; 
            if (!alpha)
				rect(game->img, x_offset + i * cw, start_y + y, cw, 1, pixel_colour);
    	    ty += ty_step;
    	    y++;
    	}
	}
}

void c3d_player_look(t_game *game) {
    t_ray this_ray;
    t_point closest, second_closest;
    t_bound *closest_wall, *second_closest_wall;
    float pt_dist, second_pt_dist;
    double ray_angle;
    int has_collided;
    float max_dist, second_max_dist;
    float i = 0;
    int j;

    while (i < 280) {
        has_collided = 0;
        max_dist = 100000;
        second_max_dist = 100000;
        this_ray.pos.x = game->player.pos.x;
        this_ray.pos.y = game->player.pos.y;
        this_ray.rot = get_safe_angle(game->player.rot + i*0.25 - 35);
        closest.x = -1;
        closest.y = -1;
        second_closest.x = -1;
        second_closest.y = -1;
        j = 0;

        while (game->walls[j]) {
            t_point *point = ray_cast(game->walls[j], &this_ray);
            if (point)
			{
                has_collided = 1;
                pt_dist = get_raylength(this_ray, *point);
                if (pt_dist != -1 && pt_dist < max_dist)
				{
                    second_max_dist = max_dist;
                    second_closest = closest;
                    second_closest_wall = closest_wall;
                    max_dist = pt_dist;
                    closest = *point;
                    closest_wall = game->walls[j];
				}
				else if (pt_dist != -1 && pt_dist < second_max_dist) 
				{
                    second_max_dist = pt_dist;
                    second_closest = *point;
                    second_closest_wall = game->walls[j];
                }
                free(point);
            }
            j++;
        }
        ray_angle = fabs(this_ray.rot - game->player.rot) * M_PI / 180.0;
        pt_dist = (200 / (get_raylength(this_ray, closest)* cos(ray_angle))) * 200;
		if (this_ray.rot == game->player.rot)
		{
			game->closest_wall_dir = closest_wall->direction;
			game->pt_dist = pt_dist;
		}
        second_pt_dist = (200 / (get_raylength(this_ray, second_closest)* cos(ray_angle))) * 200;
        if (has_collided)
		{
			if (closest_wall->direction == DOOR)
				c3d_draw_projection(game, second_pt_dist, i, second_closest.x, second_closest.y, 
				second_closest_wall);
			c3d_draw_projection(game, pt_dist, i, closest.x, closest.y, closest_wall);
		}
        i++;
    }
}
