/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 14:36:40 by ivanderw          #+#    #+#             */
/*   Updated: 2023/10/03 20:35:24 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
			"images/gun_sprite.xpm", &width, &height);
	game->e_texture = mlx_xpm_file_to_image(game->mlx,
			"images/e_msg.xpm", &width, &height);
	game->title_texture = mlx_xpm_file_to_image(game->mlx,
			"images/title_screen.xpm", &width, &height);
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
	m_game->img = mlx_new_image(m_game->mlx, m_game->w_width, m_game->w_height);
	mlx_hook(m_game->mlx_win, 2, 1L<<0, key_press, m_game);	 
	mlx_hook(m_game->mlx_win, 3, 1L<<0, key_release, m_game);
	mlx_hook(m_game->mlx_win, 6, 0, &mouse_move, m_game);
	mlx_hook(m_game->mlx_win, 17, 0, on_x_press, m_game);
	mlx_loop_hook(m_game->mlx, frame_refresh, m_game);	
	mlx_loop(m_game->mlx);
	return (0);
}
