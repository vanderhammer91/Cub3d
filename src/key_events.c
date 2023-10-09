/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 10:55:48 by ivanderw          #+#    #+#             */
/*   Updated: 2023/10/09 12:40:56 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_events.h"

int	key_press(int keycode, t_game *game)
{
	if (keycode == 53)
		ft_start_exit("", game);
	if (game->keys.l_key_down == 0 && keycode == 0)
		game->keys.l_key_down = 1;
	else if (game->keys.d_key_down == 0 && keycode == 1)
		game->keys.d_key_down = 1;
	else if (game->keys.r_key_down == 0 && keycode == 2)
		game->keys.r_key_down = 1;
	else if (game->keys.u_key_down == 0 && keycode == 13)
		game->keys.u_key_down = 1;
	else if (game->keys.e_key_down == 0 && keycode == 14)
		game->keys.e_key_down = 1;
	else if (game->keys.sh_key_down == 0 && keycode == 257)
		game->keys.sh_key_down = 1;
	else if (game->keys.sp_key_down == 0 && keycode == 49)
		game->keys.sp_key_down = 1;
	else if (game->keys.enter_key_down == 0 && keycode == 36)
		game->keys.enter_key_down = 1;
	else if (game->keys.r_rot_key_down == 0 && keycode == 123)
		game->keys.r_rot_key_down = 1;
	else if (game->keys.l_rot_key_down == 0 && keycode == 124)
		game->keys.l_rot_key_down = 1;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == 0)
		game->keys.l_key_down = 0;
	else if (keycode == 1)
		game->keys.d_key_down = 0;
	else if (keycode == 2)
		game->keys.r_key_down = 0;
	else if (keycode == 13)
		game->keys.u_key_down = 0;
	else if (keycode == 14)
		game->keys.e_key_down = 0;
	else if (keycode == 49)
		game->keys.sp_key_down = 0;
	else if (keycode == 257)
		game->keys.sh_key_down = 0;
	else if (keycode == 36)
		game->keys.enter_key_down = 0;
	else if (keycode == 124)
		game->keys.l_rot_key_down = 0;
	else if (keycode == 123)
		game->keys.r_rot_key_down = 0;
	else if (keycode == 53)
		ft_start_exit("ESC", game);
	return (0);
}

int	mouse_move(int x, int y, t_game *game)
{
	(void)y;
	if (x > game->prev_x)
	{
		game->player.rot += (x - game->prev_x) * 0.15;
		if (game->player.rot > 360)
			game->player.rot -= 360;
	}
	else if (x < game->prev_x)
	{
		game->player.rot += (x - game->prev_x) * 0.15;
		if (game->player.rot < 0)
			game->player.rot += 360;
	}
	game->prev_x = x;
	return (0);
}
