/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:09:20 by ivanderw          #+#    #+#             */
/*   Updated: 2023/10/07 16:27:50 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"


void	c3d_draw_projection(t_game *game, float raylength, int i, int ray_x, int ray_y, t_bound *closest_wall)
{
	int		y; 
	int		start_y;
	float	ty;
	float	ty_step;
	float	tx;
	int		x_offset = 0;
	int 	y_offset = 500;
	int		cw = 5;
	int		pixel_colour;
	int		img_state;
	t_point	start;
	t_point end;

	y = 0;
 	if (closest_wall->type == SOUTH)
	{
    	start_y = y_offset - raylength * 0.5;
    	ty = 0;
    	ty_step = 64.0 / (float)raylength;
		tx = (int)(ray_x) % 64;
		tx = 63 - tx;
    	while (y < raylength)
    	{
    	  	pixel_colour = retrieve_colour(game->t_lib.south_texture, tx, ty);
			if (closest_wall->texture == PILLAR)
				pixel_colour = retrieve_colour(game->t_lib.pillar_texture, tx, ty);
			pixel_colour = shade_pixel(pixel_colour, raylength);

			start.x = x_offset + i * cw;
			start.y = start_y + y;
			end.x = cw;
			end.y = 1;
			rect(game->img, &start, &end, pixel_colour);
			//rect(game->img, x_offset + i * cw, start_y + y, cw, 1, pixel_colour);
    	    ty += ty_step;
    	    y++;
    	}
	}
 	else if (closest_wall->type == NORTH)
	{
    	start_y = y_offset - raylength * 0.5;
    	ty = 0;
    	ty_step = 64.0 / (float)raylength;
		tx = (int)(ray_x) % 64;
    	while (y < raylength)
    	{
    	 	pixel_colour = retrieve_colour(game->t_lib.north_texture, tx, ty);
			if (closest_wall->texture == PILLAR)
				pixel_colour = retrieve_colour(game->t_lib.pillar_texture, tx, ty);
			pixel_colour = shade_pixel(pixel_colour, raylength);
			start.x = x_offset + i * cw;
			start.y = start_y + y;
			end.x = cw;
			end.y = 1;
			rect(game->img, &start, &end, pixel_colour);
			//rect(game->img, x_offset + i * cw, start_y + y, cw, 1, pixel_colour);
    	    ty += ty_step;
    	    y++;
    	}
	}
	else if (closest_wall->type == EAST)
	{
    	start_y = y_offset - raylength * 0.5;
    	ty = 0;
    	ty_step = 64.0 / (float)raylength;
		tx = (int)(ray_y) % 64;
    	while (y < raylength)
    	{
    	  	pixel_colour = retrieve_colour(game->t_lib.east_texture, tx, ty);
			if (closest_wall->texture == PILLAR)
				pixel_colour= retrieve_colour(game->t_lib.pillar_texture, tx, ty);
			pixel_colour = shade_pixel(pixel_colour, raylength);
			start.x = x_offset + i * cw;
			start.y = start_y + y;
			end.x = cw;
			end.y = 1;
			rect(game->img, &start, &end, pixel_colour);
			//rect(game->img, x_offset + i * cw, start_y + y, cw, 1, pixel_colour);
    	    ty += ty_step;
    	    y++;
    	}
	}
 	else if (closest_wall->type == WEST)
	{
    	start_y = y_offset - raylength * 0.5;
    	ty = 0;
    	ty_step = 64.0 / (float)raylength;
		tx = (int)(ray_y) % 64;
		tx = 63 - tx;
    	while (y < raylength)
    	{
    	 	pixel_colour = retrieve_colour(game->t_lib.west_texture, tx, ty);
			if (closest_wall->texture == PILLAR)
				pixel_colour= retrieve_colour(game->t_lib.pillar_texture, tx, ty);
			pixel_colour = shade_pixel(pixel_colour, raylength);
			start.x = x_offset + i * cw;
			start.y = start_y + y;
			end.x = cw;
			end.y = 1;
			rect(game->img, &start, &end, pixel_colour);
			//rect(game->img, x_offset + i * cw, start_y + y, cw, 1, pixel_colour);
    	    ty += ty_step;
    	    y++;
    	}
	}
	else if (closest_wall->type == AD)
	{
		img_state = game->walls[game->cwi]->img_state;
		start_y = y_offset - raylength * 0.5;
    	ty = 0;
    	ty_step = 64.0 / (float)raylength;
		tx = (int)(ray_x) % 128;
    	while (y < raylength)
    	{
    	  	pixel_colour = retrieve_colour(game->t_lib.ad_texture, tx * 2, ty + img_state * 64);
			pixel_colour = shade_pixel(pixel_colour, raylength);
			if (pixel_colour != 0x000000)
			{
				start.x = x_offset + i * cw;
				start.y = start_y + y;
				end.x = cw;
				end.y = 1;
				rect(game->img, &start, &end, pixel_colour);
				//rect(game->img, new_point(x_offset + i * cw, start_y + y), new_point(cw, 1), pixel_colour);
				//rect(game->img, x_offset + i * cw, start_y + y, cw, 1, pixel_colour);
			}
    	    ty += ty_step;
    	    y++;
    	}
	}
 	else if (closest_wall->type == DOOR)
	{
		img_state = game->walls[game->cwi]->img_state;
		start_y = y_offset - raylength * 0.5;
    	ty = 0;
    	ty_step = 128.0 / (float)raylength;
		if (closest_wall->is_vert == 0)
    		tx = (int)(ray_x) % 128;
		else
    		tx = (int)(ray_y) % 128;
    	while (y < raylength)
    	{
    	 	pixel_colour = retrieve_colour(game->t_lib.door_texture, tx * 2,
					ty + img_state * 128);
			int alpha = (pixel_colour >> 24) & 0xFF; 
            if (!alpha)
			{
				pixel_colour = shade_pixel(pixel_colour, raylength);
				start.x = x_offset + i * cw;
				start.y = start_y + y;
				end.x = cw;
				end.y = 1;
				rect(game->img, &start, &end, pixel_colour);
				//rect(game->img, new_point(x_offset + i * cw, start_y + y), new_point(cw, 1), pixel_colour);
				//rect(game->img, x_offset + i * cw, start_y + y, cw, 1, pixel_colour);
			}
    	    ty += ty_step;
    	    y++;
    	}
	}	
	else if (closest_wall->type == EXIT)
	{
		img_state = game->walls[game->cwi]->img_state;
		start_y = y_offset - raylength * 0.5;
    	ty = 0;
    	ty_step = 128.0 / (float)raylength;
		if (closest_wall->is_vert == 0)
    		tx = (int)(ray_x) % 128;
		else
    		tx = (int)(ray_y) % 128;
    	while (y < raylength)
    	{
    	 	pixel_colour = retrieve_colour(game->t_lib.exit_texture, tx * 2,
					ty + img_state * 128);
			pixel_colour = shade_pixel(pixel_colour, raylength);
			start.x = x_offset + i * cw;
			start.y = start_y + y;
			end.x = cw;
			end.y = 1;
			rect(game->img, &start, &end, pixel_colour);
			//rect(game->img, new_point(x_offset + i * cw, start_y + y), new_point(cw, 1), pixel_colour);
			//rect(game->img, x_offset + i * cw, start_y + y, cw, 1, pixel_colour);
    	    ty += ty_step;
    	    y++;
    	}

	}

}

void c3d_player_cast(t_game *game) {
    t_ray	this_ray;
    t_point	closest, second_closest;
    t_bound	*closest_wall, *second_closest_wall;
    float	pt_dist, second_pt_dist;
    double	ray_angle;
    int		has_collided;
    float 	max_dist, second_max_dist;
    float	i = 0;
    int		j;

    while (i < 280)
	{
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
        while (game->walls[j])
		{
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
					game->cwi = j;
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
		if (pt_dist > 3000)
			pt_dist = 3000;
		if (this_ray.rot == game->player.rot)
		{
			game->closest_wall_dir = closest_wall->type;
			game->pt_dist = pt_dist;
		}
        second_pt_dist = (200 / (get_raylength(this_ray, second_closest)* cos(ray_angle))) * 200;
		if (second_pt_dist > 3000)
			second_pt_dist = 3000;
        if (has_collided)
		{
			if (closest_wall->type == DOOR || closest_wall->type == AD)
				c3d_draw_projection(game, second_pt_dist, i, second_closest.x, second_closest.y, 
				second_closest_wall);
			c3d_draw_projection(game, pt_dist, i, closest.x, closest.y, closest_wall);
		}
        i++;
    }
}
