/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 10:55:03 by ivanderw          #+#    #+#             */
/*   Updated: 2023/10/03 16:16:53 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init_bounds.h"

t_game *initialize_game(void)
{
    t_game *game = malloc(sizeof(t_game));
    if (game == NULL) {
        return NULL;
    }
	game->prev_x = 0;
    game->mlx = NULL;
    game->mlx_win = NULL;
	game->w_width = 1200;
	game->w_height = 1000;
	game->door_state = 0;
	game->true_state = 0;
	game->raw = NULL;
    game->num_walls = 0;
	game->player.rb = 0;
	game->player.lb = 0;
	game->player.ub = 0;
	game->player.db = 0;
	game->skycolour = 0x000066;
	game->floorcolour = 0x000000;
	game->keys.U_KEY_DOWN = 0;
	game->keys.D_KEY_DOWN = 0;
	game->keys.L_KEY_DOWN = 0;
	game->keys.R_KEY_DOWN = 0;
	game->keys.SH_KEY_DOWN = 0;
	game->keys.L_ROT_KEY_DOWN = 0;
	game->keys.R_ROT_KEY_DOWN = 0;
	game->gun_state = 7;

	return game;
} 

