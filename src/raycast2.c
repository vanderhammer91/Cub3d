/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:33:41 by ivanderw          #+#    #+#             */
/*   Updated: 2023/10/07 16:35:37 by ivanderw         ###   ########.fr       */
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

