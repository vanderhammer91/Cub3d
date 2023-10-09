/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 14:36:40 by ivanderw          #+#    #+#             */
/*   Updated: 2023/10/09 19:08:03 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game			*m_game;
	t_parsed_data	*data;

	if (argc != 2)
		return (1);
	data = file_to_data(argv[1]);
	if (!data)
		return (printf("Error\n"), 0);
	debug_print_parsed_data(data);
	m_game = c3d_initialize_game(data);
	c3d_set_wall_bounds(m_game);
	c3d_set_player_pos(m_game);
	m_game->mlx = mlx_init();
	m_game->mlx_win = mlx_new_window(m_game->mlx, W_WIDTH,
			W_HEIGHT, "Cub3d");
	c3d_initialize_textures(m_game, data);
	m_game->img = mlx_new_image(m_game->mlx, W_WIDTH, W_HEIGHT);
	mlx_hook(m_game->mlx_win, 2, 1L << 0, key_press, m_game);
	mlx_hook(m_game->mlx_win, 3, 1L << 0, key_release, m_game);
	mlx_hook(m_game->mlx_win, 6, 0, &mouse_move, m_game);
	mlx_hook(m_game->mlx_win, 17, 0, on_x_press, m_game);
	mlx_loop_hook(m_game->mlx, frame_refresh, m_game);
	mlx_loop(m_game->mlx);
	delete_parsed_data(data);
	return (0);
}
