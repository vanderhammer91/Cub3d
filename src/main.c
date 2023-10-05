/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 14:36:40 by ivanderw          #+#    #+#             */
/*   Updated: 2023/10/05 19:12:37 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	c3d_initialize_textures(t_game *game, t_parsed_data *d)
{
    int	width;
	int	height;

	game->north_texture = mlx_xpm_file_to_image(game->mlx,
			d->north_texture, &width, &height);
	game->east_texture = mlx_xpm_file_to_image(game->mlx,
			d->east_texture, &width, &height);
  	game->south_texture = mlx_xpm_file_to_image(game->mlx,
			d->south_texture, &width, &height);
    game->west_texture = mlx_xpm_file_to_image(game->mlx,
			d->west_texture, &width, &height);
	if (!game->north_texture
			|| !game->east_texture
			|| !game->south_texture
			|| !game->west_texture)
	{
		ft_start_exit("Error: Texture file not found\n", game);
	}

	//bonus
	
    game->door_texture = mlx_xpm_file_to_image(game->mlx,
			"images/door/door_128.xpm", &width, &height);
    game->gun_texture = mlx_xpm_file_to_image(game->mlx,
			"images/gun_sprite.xpm", &width, &height);
	game->e_texture = mlx_xpm_file_to_image(game->mlx,
			"images/e_msg.xpm", &width, &height);
	game->title_texture = mlx_xpm_file_to_image(game->mlx,
			"images/title_screen.xpm", &width, &height);
	game->pillar_texture = mlx_xpm_file_to_image(game->mlx,
			"images/pillar/pillar3.xpm", &width, &height);
	game->exit_texture = mlx_xpm_file_to_image(game->mlx,
			"images/exit.xpm", &width, &height);
	game->exit_msg_texture = mlx_xpm_file_to_image(game->mlx,
			"images/you_win.xpm", &game->msg_width, &game->msg_height);
	if (!game->exit_msg_texture)
		printf("bazinga!\n");
		
}


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
	debug_print_parsed_data(data);
	m_game	= initialize_game(data);
	//c3d_set_raw(argv, m_game);
	//c3d_print_raw(m_game);
	c3d_set_wall_bounds(m_game);
	c3d_set_player_pos(m_game);
	
	m_game->mlx = mlx_init();
	m_game->mlx_win = mlx_new_window(m_game->mlx, m_game->w_width,
		m_game->w_height, "Cub3d");
	c3d_initialize_textures(m_game, data);
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
