/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 10:55:03 by ivanderw          #+#    #+#             */
/*   Updated: 2023/10/09 16:30:46 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "initialize.h"

int	rgb_to_hex(int r, int g, int b)
{
	int	res;

	res = 0;
	res = (r & 0xff) << 16 | (g & 0xff) << 8 | (b & 0xff);
	return (res);
}

void	c3d_initialize_key_states(t_game *game)
{
	game->keys.U_KEY_DOWN = 0;
	game->keys.D_KEY_DOWN = 0;
	game->keys.L_KEY_DOWN = 0;
	game->keys.R_KEY_DOWN = 0;
	game->keys.SH_KEY_DOWN = 0;
	game->keys.SP_KEY_DOWN = 0;
	game->keys.L_ROT_KEY_DOWN = 0;
	game->keys.R_ROT_KEY_DOWN = 0;
	game->keys.ENTER_KEY_DOWN = 0;
}

t_game	*c3d_initialize_game(t_parsed_data *d)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (game == NULL)
		return (NULL);
	game->prev_x = 0;
	game->mlx = NULL;
	game->mlx_win = NULL;
	game->speed = 0;
	game->game_state = 0;
	game->door_state = 0;
	game->true_state = 0;
	game->ad_state = 0;
	game->splash_state = 0;
	game->raw = d->map;
	game->num_walls = 0;
	game->player.rb = 0;
	game->player.lb = 0;
	game->player.ub = 0;
	game->player.db = 0;
	game->player.rot = 0;
	game->player.pos.x = 0;
	game->player.pos.y = 0;
	game->skycolour = rgb_to_hex(d->ceiling_r, d->ceiling_g, d->ceiling_b);
	game->floorcolour = rgb_to_hex(d->floor_r, d->floor_g, d->floor_b);
	c3d_initialize_key_states(game);
	game->gun_state = 7;
	game->parsed_data = d;
	return (game);
}

void	c3d_initialize_textures(t_game *game, t_parsed_data *d)
{
	int	width;
	int	height;

	game->t_lib.north_texture = mlx_xpm_file_to_image(game->mlx,
			d->north_texture, &width, &height);
	game->t_lib.east_texture = mlx_xpm_file_to_image(game->mlx,
			d->east_texture, &width, &height);
	game->t_lib.south_texture = mlx_xpm_file_to_image(game->mlx,
			d->south_texture, &width, &height);
	game->t_lib.west_texture = mlx_xpm_file_to_image(game->mlx,
			d->west_texture, &width, &height);
	if (!game->t_lib.north_texture
		|| !game->t_lib.east_texture
		|| !game->t_lib.south_texture
		|| !game->t_lib.west_texture)
	{
		ft_start_exit("Error: Texture file not found\n", game);
	}
	c3d_initialize_textures2(game);
}

void	c3d_initialize_textures2(t_game *game)
{
	int	width;
	int	height;

	game->t_lib.door_texture = mlx_xpm_file_to_image(game->mlx,
			"images/door_128.xpm", &width, &height);
	game->t_lib.e_texture = mlx_xpm_file_to_image(game->mlx,
			"images/e_msg.xpm", &width, &height);
	game->t_lib.exit_msg_texture = mlx_xpm_file_to_image(game->mlx,
			"images/you_win.xpm", &game->msg_width, &game->msg_height);
	game->t_lib.exit_texture = mlx_xpm_file_to_image(game->mlx,
			"images/exit.xpm", &width, &height);
	game->t_lib.gun_texture = mlx_xpm_file_to_image(game->mlx,
			"images/gun_sprite.xpm", &width, &height);
	game->t_lib.pillar_texture = mlx_xpm_file_to_image(game->mlx,
			"images/pillar/pillar1.xpm", &width, &height);
	game->t_lib.title_texture = mlx_xpm_file_to_image(game->mlx,
			"images/title_screen.xpm", &width, &height);
	game->t_lib.ad_texture = mlx_xpm_file_to_image(game->mlx,
			"images/ad_64.xpm", &width, &height);
}
