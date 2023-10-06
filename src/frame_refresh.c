/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_refresh.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 10:18:51 by ivanderw          #+#    #+#             */
/*   Updated: 2023/10/06 19:52:24 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frame_refresh.h"
 
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
	{
		game->walls[i]->is_active = 0;
	}
	else
	{
		game->walls[i]->is_active = 1;
	}
}

void	check_walls_3(t_game *game, int i)
{
	game->walls[i]->img_state++;
	if 	(game->walls[i]->img_state > 60)
		game->walls[i]->img_state = 0;
}

void	c3d_check_walls_call(t_game *game)
{
	int	i;

	i = 0;
	while (game->walls[i])
	{
		if (game->walls[i]->type == DOOR)
		{	
			check_walls_2(game, i);
		}
		else if(game->walls[i]->type == AD)
		{
			check_walls_3(game, i);
		}
		i++;
	}
}

void draw_gun_state(t_game *game, int gun_state, int x_off, int y_off)
{
    int sprite_y = gun_state * 523;  
    int bpp;
    int size_line;
    int endian;
	int	colour;
	int alpha;
    int *texture_data = (int*)mlx_get_data_addr(game->t_lib.gun_texture, &bpp, &size_line, &endian);
	int m_off = (((int)(game->player.pos.x) + (int)(game->player.pos.y))  % 80) * 0.2;
	int	y;
	int	x;
	int	texture_y;

    for (y = 0; y < 523; y++)
    {
        texture_y = sprite_y + y;
        for (x = 0; x < 1000; x++)
        {
            colour = texture_data[texture_y * 1000 + x];
			alpha = (colour >> 24) & 0xFF; 
            if (!alpha)
				img_pixel_put(game->img, x + x_off, y + y_off + m_off, colour);            	
        }
    }
}

void	c3d_check_gun_state(t_game *game)
{
		if (game->keys.SP_KEY_DOWN && game->gun_state == 7)
		{
			game->gun_state++;
		}
		if (game->gun_state > 7)
		{
			game->gun_state++;
			if (game->gun_state > 10)
			{
				game->gun_state = 0;
			}
		}
		else if (game->gun_state < 7)
		{
			game->gun_state++;
		}
}

void	frame_refresh_title(t_game *game)
{
    int bpp;
    int size_line;
    int endian;
	int	colour;	
	int sprite_y;
	int	*texture_data;
	int	x;
	int	y;

	sprite_y = game->splash_state * W_HEIGHT; 
   	texture_data = NULL;	
    texture_data = (int*)mlx_get_data_addr(game->t_lib.title_texture, &bpp, &size_line, &endian);
	mlx_clear_window(game->mlx, game->mlx_win);
	game->img = mlx_new_image(game->mlx, W_WIDTH, W_HEIGHT);
	if (game->keys.ENTER_KEY_DOWN)
		game->game_state = 1;
	game->frame++;
	if (game->frame >= 8)
	{
		game->frame = 0;
		game->splash_state++;
		if (game->splash_state > 1)
		{
			game->splash_state = 0;
		}		
	}
	for (y = 0; y < W_HEIGHT; y++)
    {
        for (x = 0; x < W_WIDTH; x++)
        {
          colour = texture_data[((y + sprite_y) * W_WIDTH) + x];
			img_pixel_put(game->img, x, y, colour);            	
        }
    }		
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img, 0, 0);
	mlx_destroy_image(game->mlx, game->img);
}

void	frame_refresh_exit(t_game *game)
{
	game->frame++;
	if (game->frame >= 80)
		ft_start_exit("YOU WIN!\n", game);
	mlx_clear_window(game->mlx, game->mlx_win);
	game->img = mlx_new_image(game->mlx, W_WIDTH, W_HEIGHT);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->t_lib.exit_msg_texture, 
			(W_WIDTH / 2) - (game->msg_width / 2), (W_HEIGHT / 2) - (game->msg_height / 2));
	mlx_destroy_image(game->mlx, game->img);
}

int	frame_refresh_main(t_game *game)
{
	t_point	start;
	t_point	end;
		
	game->frame++;
	if (game->frame >= 8)
		game->frame = 0;
	if (game->frame % 2 == 0)
	{
		game->ad_state++;
		c3d_check_walls_call(game);
		c3d_check_gun_state(game);
	}
	mlx_clear_window(game->mlx, game->mlx_win);
	game->img = mlx_new_image(game->mlx, 1400, 1000);	
	c3d_update_player_pos(game);

	//floor and sky colour from .CUB
	
	set_point(&start, 0, 0);
	set_point(&end, 1200, 500);
	rect(game->img, &start, &end, game->skycolour);
	set_point(&start, 0, 500);
	set_point(&end, 1200, 500);
	rect(game->img, &start, &end, game->floorcolour);

	//raycasting
	c3d_player_cast(game);

	//output
	set_point(&start, 600, 540);
	set_point(&end, 10, 10);
	rect(game->img, &start, &end, 0xFFFFFF);
	c3d_draw_minimap(game);
	test_hitrays(game);
	draw_gun_state(game, game->gun_state, 350, 475);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img, 0, 0);
	c3d_draw_overlay(game);
	mlx_destroy_image(game->mlx, game->img);
	return (0);
}

int	frame_refresh(t_game *game)
{
	if (game->game_state == 0)
		frame_refresh_title(game);
	else if (game->game_state == 1)
		frame_refresh_main(game);
	else if (game->game_state == 2)
		frame_refresh_exit(game);
	return (0);
}
