/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 14:36:40 by ivanderw          #+#    #+#             */
/*   Updated: 2023/09/26 16:37:17 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "textures.h"

int	prev_x = 0;


int	main(int argc, char **argv)
{
	t_game	*m_game;
	int width;
	int height;

	if (argc != 2)
		return (1);
	m_game	= initialize_game();
	c3d_set_raw(argv, m_game);
	c3d_print_raw(m_game);
	c3d_set_wall_bounds(m_game);
	c3d_set_player_pos(m_game);
	
	//	c3d_print_bounds(m_game);



	m_game->mlx = mlx_init();
	m_game->mlx_win = mlx_new_window(m_game->mlx, m_game->w_width,
		m_game->w_height, "Cub3d");
    m_game->north_texture = mlx_xpm_file_to_image(m_game->mlx, "images/north.xpm", &width, &height);
	m_game->east_texture = mlx_xpm_file_to_image(m_game->mlx, "images/east.xpm", &width, &height);
  	m_game->south_texture = mlx_xpm_file_to_image(m_game->mlx, "images/south.xpm", &width, &height);
    m_game->west_texture = mlx_xpm_file_to_image(m_game->mlx, "images/west.xpm", &width, &height);

	m_game->img = mlx_new_image(m_game->mlx, m_game->w_width, m_game->w_height);	
	mlx_hook(m_game->mlx_win, 2, 1L<<0, key_press, m_game);	 
	mlx_hook(m_game->mlx_win, 3, 1L<<0, key_release, m_game);
	mlx_hook(m_game->mlx_win, 6, 0, &mouse_move, m_game);
	mlx_hook(m_game->mlx_win, 17, 0, on_x_press, m_game);
	mlx_loop_hook(m_game->mlx, frame_refresh, m_game);	
	mlx_loop(m_game->mlx);

	return (0);
}
