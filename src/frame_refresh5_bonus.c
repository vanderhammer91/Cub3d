/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_refresh5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 20:28:17 by ivanderw          #+#    #+#             */
/*   Updated: 2023/10/06 20:55:32 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frame_refresh.h"

void	frame_refresh_title_put_image(t_game *game, t_img_handler m_state)
{
	int	x;
	int	y;

	y = 0;
	while (y < W_HEIGHT)
	{
		x = 0;
		while (x < W_WIDTH)
		{
			m_state.colour = m_state.texture_data[((y + m_state.sprite_y)
					* W_WIDTH) + x];
			img_pixel_put(game->img, x, y, m_state.colour);
			x++;
		}
		y++;
	}
}

void	frame_refresh_title(t_game *game)
{
	t_img_handler	m_state;

	m_state.sprite_y = game->splash_state * W_HEIGHT;
	m_state.texture_data = NULL;
	m_state.texture_data = (int *)mlx_get_data_addr(game->t_lib.title_texture,
			&m_state.bpp, &m_state.size_line, &m_state.endian);
	mlx_clear_window(game->mlx, game->mlx_win);
	game->img = mlx_new_image(game->mlx, W_WIDTH, W_HEIGHT);
	if (game->keys.enter_key_down)
		game->game_state = 1;
	game->frame++;
	if (game->frame >= 8)
	{
		game->frame = 0;
		game->splash_state++;
		if (game->splash_state > 1)
			game->splash_state = 0;
	}
	frame_refresh_title_put_image(game, m_state);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img, 0, 0);
	mlx_destroy_image(game->mlx, game->img);
}
