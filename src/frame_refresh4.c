/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_refresh4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 19:56:27 by ivanderw          #+#    #+#             */
/*   Updated: 2023/10/06 20:23:54 by ivanderw         ###   ########.fr       */
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
	else if (game->walls[i]->door_state == 18
		|| game->walls[i]->door_state == 19)
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
	if (game->walls[i]->img_state > 60)
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
		else if (game->walls[i]->type == AD)
		{
			check_walls_3(game, i);
		}
		i++;
	}
}

typedef struct s_gunstate
{
	int	sprite_y;
	int	bpp;
	int	size_line;
	int	endian;
	int	colour;
	int	alpha;
	int	*texture_data;
	int	m_off;
	int	texture_y;
}		t_gunstate;

void	draw_gun_state(t_game *game, int gun_state, int x_off, int y_off)
{
	t_gunstate	gunst;
	int			x;
	int			y;

	gunst.sprite_y = gun_state * 523;
	gunst.texture_data = (int *)mlx_get_data_addr(game->t_lib.gun_texture,
			&gunst.bpp, &gunst.size_line, &gunst.endian);
	gunst.m_off = (((int)(game->player.pos.x)
				+ (int)(game->player.pos.y)) % 80) * 0.2;
	y = 0;
	while (y < 523)
	{
		gunst.texture_y = gunst.sprite_y + y;
		x = 0;
		while (x < 1000)
		{
			gunst.colour = gunst.texture_data[gunst.texture_y * 1000 + x];
			gunst.alpha = (gunst.colour >> 24) & 0xFF;
			if (!gunst.alpha)
				img_pixel_put(game->img, x + x_off, y + y_off + gunst.m_off,
					gunst.colour);
			x++;
		}
		y++;
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
