/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_refresh.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 10:18:51 by ivanderw          #+#    #+#             */
/*   Updated: 2023/09/26 16:18:05 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "frame_refresh.h"
#include <stdio.h>
#include <math.h>  // For sqrt function

double get_safe_angle(double angle)
{
	while (angle < 0)
		angle +=360;
	while (angle > 360)
		angle -= 360;
	return (angle);
}

int	c3d_draw_map_bounds(t_game *game)
{
	int	i;
	int	j;
	int	map_height;
	int	map_width;
	t_point	start;
	t_point end;

	i = 0;
	map_height = get_mapheight(game);
	map_width = ft_strlen(game->raw[i]);
	while (game->raw[i])
	{
		j = 0;
		while (game->raw[i][j])
		{
			if (game->raw[i][j] == '1')
			{
				if ((i - 1) > -1 && game->raw[i - 1][j] == '0')
				{
					//clockwise, drawing top face.
					start.y = i * 80 ;
					start.x = j * 80 ;
					end.y = i * 80;
					end.x = (j + 1) * 80 ;
					line(game->img, start, end, 0x00FF00);
				}
				if ((j + 1) < map_width && game->raw[i][j + 1] == '0')
				{					
					//drawing right face:
					start.y = i * 80 ;
					start.x = (j + 1) * 80 ;
					end.y = (i + 1) * 80;
					end.x = (j + 1) * 80 ;
					line(game->img, start, end, 0x0000FF);
				}
				if ((i + 1) < map_height && game->raw[i + 1][j] == '0')
				{				
					//clockwise, drawing bot face.
					start.y = (i + 1) * 80 ;
					start.x = (j + 1) * 80 ;
					end.y = (i + 1) * 80;
					end.x = j * 80 ;
					line(game->img, start, end, 0xFF0000);
				}
				if ((j - 1) > -1 && game->raw[i][j - 1] == '0')
				{			
				//drawing left face:
				start.y = (i + 1) * 80 ;
				start.x = j * 80 ;
				end.y = i * 80;
				end.x = j * 80 ;
				line(game->img, start, end, 0x00FFFF);	
				}			
			}
			else if (game->raw[i][j] == '0')
			{
			}
			//	rect(game->img, i * 80, j * 80, 79, 79, 0xFFFFFF);
			j++;
		}	
		i++;
	}
	return (0);
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
	if (game->keys.U_KEY_DOWN&& !game->keys.D_KEY_DOWN)
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

	start.x = game->player.pos.x;
	start.y = game->player.pos.y;

	//green line in the direction the player is facing.
	unitVector.x = cos(radians) * radius;
	unitVector.y = sin(radians) * radius;
	end.x = start.x + unitVector.x;
	end.y = start.y + unitVector.y;
	line(game->img, start, end, 0x000000);
	return (0);
}

int	frame_refresh(t_game *game)
{	
	mlx_clear_window(game->mlx, game->mlx_win);
	game->img = mlx_new_image(game->mlx, 1600, 800);	
	
	//update
	c3d_update_player_pos(game);			
	
	//draw minimap and player circle
//	c3d_draw_bounds(game, game->img);
//	c3d_draw_map_bounds(game);
//	filled_circle(game->img, game->player.pos.x, game->player.pos.y, 10, 0xFF0000);

	//roof colour
	rect(game->img, 0, 0, 1000, 400, 0x000066);
	
	//floor colour
	rect(game->img, 0, 400, 1000, 400, 0x000000);

	c3d_player_look(game);
	draw_dir_arrow(game);
	test_hitrays(game);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img, 0, 0);



	mlx_destroy_image(game->mlx, game->img);
	return (0);
}
