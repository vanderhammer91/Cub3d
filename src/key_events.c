/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 10:55:48 by ivanderw          #+#    #+#             */
/*   Updated: 2023/09/28 18:56:31 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_events.h"

extern int prev_x;

int	key_press(int keycode, t_game *game)
{
	//printf("hello from keycode %d!\n", keycode);
	
	if (keycode == 53)
		ft_start_exit("ESC", game);
	if (game->keys.L_KEY_DOWN == 0 && keycode == 0)
		game->keys.L_KEY_DOWN = 1;
	else if (game->keys.D_KEY_DOWN == 0 && keycode == 1)
		game->keys.D_KEY_DOWN = 1;
	else if (game->keys.R_KEY_DOWN == 0 && keycode == 2)
		game->keys.R_KEY_DOWN = 1;
	else if (game->keys.U_KEY_DOWN == 0 && keycode == 13)
		game->keys.U_KEY_DOWN = 1;
	else if (game->keys.E_KEY_DOWN == 0 && keycode == 14)
		game->keys.E_KEY_DOWN = 1;	
	else if (game->keys.SH_KEY_DOWN == 0 && keycode == 257)
		game->keys.SH_KEY_DOWN = 1;
	else if (game->keys.SP_KEY_DOWN == 0 && keycode == 49)
		game->keys.SP_KEY_DOWN = 1;
	else if (game->keys.R_ROT_KEY_DOWN == 0 && keycode == 123)
		game->keys.R_ROT_KEY_DOWN = 1;	
	else if (game->keys.L_ROT_KEY_DOWN == 0 && keycode == 124)
		game->keys.L_ROT_KEY_DOWN = 1;	
	return (0);
}

int key_release(int keycode, t_game *game)
{
	if (keycode == 0)
		game->keys.L_KEY_DOWN = 0;
	else if (keycode == 1)
		game->keys.D_KEY_DOWN = 0;
	else if (keycode == 2)
		game->keys.R_KEY_DOWN = 0;
	else if (keycode == 13)
		game->keys.U_KEY_DOWN = 0;
	else if (keycode == 14)
		game->keys.E_KEY_DOWN = 0;
	else if (keycode == 49)
		game->keys.SP_KEY_DOWN = 0;	
	else if (keycode == 257)
		
	else if (keycode == 124)
		game->keys.L_ROT_KEY_DOWN = 0;	
	else if (keycode == 123)
		game->keys.R_ROT_KEY_DOWN = 0;	
	else if (keycode == 53)
		ft_start_exit("ESC", game);
	return (0);
}

int mouse_move(int x, int y, t_game *game)
{
	(void)y;
	if (x > game->prev_x)
	{
		game->player.rot += (x - game->prev_x) * 0.3;	
		if (game->player.rot < 0)
			game->player.rot += 360; 

	}
	else if (x < game->prev_x)
	{
		game->player.rot += (x - game->prev_x) * 0.3;	
		if (game->player.rot < 0)
			game->player.rot += 360; 
	}
	game->prev_x = x;
	return 0;
}

