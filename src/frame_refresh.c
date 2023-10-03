/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_refresh.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 10:18:51 by ivanderw          #+#    #+#             */
/*   Updated: 2023/10/03 16:32:05 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "frame_refresh.h"
#include <stdio.h>
#include <math.h>  

double get_safe_angle(double angle)
{
	while (angle < 0)
		angle +=360;
	while (angle > 360)
		angle -= 360;
	return (angle);
}

int	c3d_update_player_pos(t_game *game)
{
	int	speed;
	double	radians;
	double	perp_rad;
	double new_x;
	double new_y;
	int		has_set = 0;

	radians = game->player.rot * M_PI / 180;
	perp_rad = get_safe_angle((game->player.rot + 90)) * (M_PI / 180);
	speed = 3;
	if (game->keys.SH_KEY_DOWN == 1)
		speed *= 2;
	new_x = 0;
	new_y = 0;
	if (game->keys.U_KEY_DOWN && !game->keys.D_KEY_DOWN)
	{
		new_x = game->player.pos.x + speed * cos(radians);
		new_y = game->player.pos.y + speed * sin(radians);
		has_set = 1;
	}
	else if (game->keys.D_KEY_DOWN && !game->keys.U_KEY_DOWN)
	{
		new_x = game->player.pos.x - speed * cos(radians);
		new_y = game->player.pos.y - speed * sin(radians);
		has_set = 1;
	}
	else if (game->keys.L_KEY_DOWN && !game->keys.R_KEY_DOWN)
	{
		new_x = game->player.pos.x - speed * cos(perp_rad);
		new_y = game->player.pos.y - speed * sin(perp_rad);
		has_set = 1;
	}
	else if (game->keys.R_KEY_DOWN && !game->keys.L_KEY_DOWN)
	{
		new_x = game->player.pos.x + speed * cos(perp_rad);
		new_y = game->player.pos.y + speed * sin(perp_rad);
		has_set = 1;
	}	
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
	{
		game->player.rot -= 0.3 * speed;	
		if (game->player.rot < 0)
			game->player.rot += 360;
	}
	if (game->keys.L_ROT_KEY_DOWN)
	{
		game->player.rot += 0.3 * speed;
		if (game->player.rot >= 360)
			game->player.rot -= 360;
	}
	return (0);
}

int	draw_dir_arrow(t_game *game)
{
	t_point start;
	t_point end;
	t_vector unitVector;
	double radians = game->player.rot * M_PI / 180.0;
	double radius = 15;

	start.x = 150;
	start.y = 150;	
	unitVector.x = cos(radians) * radius;
	unitVector.y = sin(radians) * radius;
	end.x = start.x + unitVector.x;
	end.y = start.y + unitVector.y;
	line(game->img, start, end, 0x00FFFF);
	return (0);
}

void	c3d_draw_overlay(t_game *game)
{
	if (game->pt_dist > 600)
	{	
		if(game->closest_wall_dir == DOOR)
		{
			mlx_put_image_to_window(game->mlx, game->mlx_win, game->e_texture, 100, 900);
			if (game->keys.E_KEY_DOWN == 1)
			{
				if (game->walls[game->closest_wall_index]->door_state == 0)
					game->walls[game->closest_wall_index]->door_state = 1;
				else if (game->walls[game->closest_wall_index]->door_state == 10)
					game->walls[game->closest_wall_index]->door_state = 11;
			}
		}
	}
}

void c3d_draw_minimap(t_game *game, void *img)
{
	int offset = 300;
	int y_bound = 300;
	int x_bound = 300;
	t_point new_start;
	t_point new_end;

	rect(game->img, 0, 0, 300, 300, 0x0c212e);
	rect(game->img, 145, 145, 10, 10, 0x00FFFF);
   for (int i = 0; i < game->num_walls; i++) {
		t_bound *wall = game->walls[i];
		new_start.x = (wall->start.x - game->player.pos.x + offset) / 2;
		new_start.y = (wall->start.y - game->player.pos.y + offset) / 2;
		new_end.x = (wall->end.x - game->player.pos.x + offset) / 2;
		new_end.y = (wall->end.y - game->player.pos.y + offset) / 2;

		if (new_start.x > x_bound)
			new_start.x = x_bound;
		if (new_start.y > y_bound)
			new_start.y = y_bound;
		if (new_end.x > x_bound)
			new_end.x = x_bound;
		if (new_end.y > y_bound)
			new_end.y = y_bound;

		if (wall->direction != DOOR)
        	line(img, new_start, new_end, 0x0000FF);
		else
		{	
			if (wall->is_active)
				line(img, new_start, new_end, 0x00FFFF);
		}
    }
	draw_dir_arrow(game);
	new_start.x = 0;
	new_start.y = 0;
	draw_square(img, new_start, 300, 0x00FFFF);
	new_start.x = 5;
	new_start.y = 5;
	draw_square(img, new_start, 290, 0x00FFFF);
}
 
void	check_walls_2(t_game *game, int i)
{
	if (game->walls[i]->door_state > 0 && game->walls[i]->door_state < 10)
	{
		game->walls[i]->door_state++;
		game->walls[i]->img_state++;
	}
	else if (game->walls[i]->door_state > 10 && game->walls[i]->door_state < 18)
	{
		game->walls[i]->door_state++;
		game->walls[i]->img_state--;
	}
	
	else if (game->walls[i]->door_state == 18 || game->walls[i]->door_state == 19)
	{
		game->walls[i]->door_state = 0;
		game->walls[i]->img_state = 0;
	}

	if (game->walls[i]->img_state > 5)
		game->walls[i]->is_active = 0;
	else
		game->walls[i]->is_active = 1;
}

void	check_walls_call(t_game *game)
{
	int	i;

	i = 0;
	while (game->walls[i])
	{
		if (game->walls[i]->direction == DOOR)
		{	
			check_walls_2(game, i);
		}
		i++;
	}
}
/*
void draw_gun_state(t_game *game, int gun_state)
{

    // Create a new image for the sprite
 	int     bpp;
    int     size_line;
    int     endian;
	int		sprite_y = gun_state * 523;	
	(void)sprite_y;
   int *data = (int*)mlx_get_data_addr(game->img, &bpp, &size_line, &endian);
   (void)data;
   // int *texture_data = (int*)mlx_get_data_addr(game->gun_texture, &bpp, &size_line, &endian);
//	(void)texture_data;
	for (int y = 0; y < 523; y++)
	{
    //	int texture_y = sprite_y + y;
    	for (int x = 0; x < 1000; x++)
    	{
    	   // data[y * 1000 + x] = texture_data[texture_y * 1000 + x];
    	}
	}
    //int y_offset = (((int)(game->player.pos.x) + (int)(game->player.pos.y))  % 80) * 0.2;
    //mlx_put_image_to_window(game->mlx, game->mlx_win, game->img, 400, 480 + y_offset);
   // mlx_destroy_image(game->mlx, game->img);
}
*/
void draw_gun_state(t_game *game, int gun_state, int x_off, int y_off)
{
    int sprite_y = gun_state * 523;  
    int     bpp;
    int     size_line;
    int     endian;
    int *texture_data = (int*)mlx_get_data_addr(game->gun_texture, &bpp, &size_line, &endian);
	int m_off = (((int)(game->player.pos.x) + (int)(game->player.pos.y))  % 80) * 0.2;
    for (int y = 0; y < 523; y++)
    {
        int texture_y = sprite_y + y;
        for (int x = 0; x < 1000; x++)
        {
            // Get the color of the pixel from the texture
            int colour = texture_data[texture_y * 1000 + x];
			int alpha = (colour >> 24) & 0xFF; 
            if (!alpha)
				img_pixel_put(game->img, x + x_off, y + y_off + m_off, colour);            	
        }
    }
}

int	frame_refresh(t_game *game)
{
	game->frame++;
	if (game->frame >= 8)
		game->frame = 0;
	if (game->frame % 2 == 0)
	{
		check_walls_call(game);	
		if (game->keys.SP_KEY_DOWN && game->gun_state == 7)
		{
			game->gun_state++;
		}
		if (game->gun_state > 7)
		{
			game->gun_state++;
			if (game->gun_state > 10)
				game->gun_state = 0;
		}
		else if (game->gun_state < 7)
		{
			game->gun_state++;
		}
	}
	mlx_clear_window(game->mlx, game->mlx_win);
	game->img = mlx_new_image(game->mlx, 2000, 2000);	

	//update
	c3d_update_player_pos(game);			
	
	//sky and floor colour respectively.
	rect(game->img, 0, 0, 1200, 500, 0x000066);
	//	rect(game->img, 0, 400, 1000, 400, game->floorcolour);

	c3d_player_look(game);
	test_hitrays(game);
	rect(game->img, 600, 550, 10, 10, 0xFFFFFF);
	c3d_draw_minimap(game, game->img);
	draw_gun_state(game, game->gun_state, 350, 475);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img, 0, 0);
	c3d_draw_overlay(game);
	mlx_destroy_image(game->mlx, game->img);

	return (0);
}
