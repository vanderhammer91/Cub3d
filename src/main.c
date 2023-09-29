/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 14:36:40 by ivanderw          #+#    #+#             */
/*   Updated: 2023/09/29 17:09:01 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "textures.h"

void	c3d_set_door_frames(t_game *game)
{
	game->door_frame[0] = "images/door/d1.xpm";
	game->door_frame[1] = "images/door/d2.xpm";
	game->door_frame[2] = "images/door/d3.xpm";
	game->door_frame[3] = "images/door/d4.xpm";
	game->door_frame[4] = "images/door/d5.xpm";
	game->door_frame[5] = "images/door/d6.xpm";
	game->door_frame[6] = "images/door/d7.xpm";
	game->door_frame[7] = "images/door/d8.xpm";
	game->door_frame[8] = "images/door/d9.xpm";
	game->door_frame[9] = "images/door/d10.xpm";
	game->door_frame[10] = "images/door/d11.xpm";
	game->door_frame[11] = "images/door/d12.xpm";
	game->door_frame[12] = "images/door/d13.xpm";
	game->door_frame[13] = "images/door/d14.xpm";
	game->door_frame[14] = "images/door/d15.xpm";
	game->door_frame[15] = "images/door/d16.xpm";
	game->door_frame[16] = "images/door/d17.xpm";
	game->door_frame[17] = "images/door/d18.xpm";
	game->door_frame[18] = "images/door/d19.xpm";
	game->door_frame[19] = "images/door/d20.xpm";
	game->door_frame[20] = "images/door/d21.xpm";
	game->door_frame[21] = "images/door/d22.xpm";
}


void	c3d_initialize_textures(t_game *game)
{
    int	width;
	int	height;

	game->north_texture = mlx_xpm_file_to_image(game->mlx,
			"images/wall.xpm", &width, &height);
	game->east_texture = mlx_xpm_file_to_image(game->mlx,
			"images/wall.xpm", &width, &height);
  	game->south_texture = mlx_xpm_file_to_image(game->mlx,
			"images/wall.xpm", &width, &height);
    game->west_texture = mlx_xpm_file_to_image(game->mlx,
			"images/wall.xpm", &width, &height);
    game->door_texture = mlx_xpm_file_to_image(game->mlx,
			"images/door/door_128.xpm", &width, &height);
    game->gun_texture = mlx_xpm_file_to_image(game->mlx,
			"images/gun4.xpm", &width, &height);
	game->e_texture = mlx_xpm_file_to_image(game->mlx,
			"images/e_msg.xpm", &width, &height);
}


int	main(int argc, char **argv)
{
	t_game	*m_game;
	if (argc != 2)
		return (1);
	m_game	= initialize_game();
	c3d_set_raw(argv, m_game);
	c3d_print_raw(m_game);
	c3d_set_wall_bounds(m_game);
	c3d_set_player_pos(m_game);
	
	m_game->mlx = mlx_init();
	m_game->mlx_win = mlx_new_window(m_game->mlx, m_game->w_width,
		m_game->w_height, "Cub3d");
	c3d_initialize_textures(m_game);
	c3d_set_door_frames(m_game);
	m_game->img = mlx_new_image(m_game->mlx, m_game->w_width, m_game->w_height);	
	mlx_hook(m_game->mlx_win, 2, 1L<<0, key_press, m_game);	 
	mlx_hook(m_game->mlx_win, 3, 1L<<0, key_release, m_game);
	mlx_hook(m_game->mlx_win, 6, 0, &mouse_move, m_game);
	mlx_hook(m_game->mlx_win, 17, 0, on_x_press, m_game);
	mlx_loop_hook(m_game->mlx, frame_refresh, m_game);	
	mlx_loop(m_game->mlx);

	return (0);
}
