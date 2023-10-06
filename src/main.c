/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 14:36:40 by ivanderw          #+#    #+#             */
/*   Updated: 2023/10/06 12:50:37 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"




int	main(int argc, char **argv)
{
	t_game	*m_game;
	t_parsed_data	*data;

	if (argc != 2)
		return (1);

	data = file_to_data(argv[1]);
	if (!data)
	{
		printf("Error\n");
		return (0);
	}
	//initialization.
	debug_print_parsed_data(data);
	m_game	= c3d_initialize_game(data);
	c3d_set_wall_bounds(m_game);
	c3d_set_player_pos(m_game);

	//mlx initialization.
	m_game->mlx = mlx_init();
	m_game->mlx_win = mlx_new_window(m_game->mlx, m_game->w_width,
		m_game->w_height, "Cub3d");
	c3d_initialize_textures(m_game, data);
	c3d_initialize_textures2(m_game);
	m_game->img = mlx_new_image(m_game->mlx, m_game->w_width, m_game->w_height);

	//key events
	mlx_hook(m_game->mlx_win, 2, 1L<<0, key_press, m_game);	 
	mlx_hook(m_game->mlx_win, 3, 1L<<0, key_release, m_game);
	mlx_hook(m_game->mlx_win, 6, 0, &mouse_move, m_game);
	mlx_hook(m_game->mlx_win, 17, 0, on_x_press, m_game);

	//every frame events.
	mlx_loop_hook(m_game->mlx, frame_refresh, m_game);	
	mlx_loop(m_game->mlx);
	delete_parsed_data(data);
	return (0);
}
