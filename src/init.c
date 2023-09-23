/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 10:55:03 by ivanderw          #+#    #+#             */
/*   Updated: 2023/09/22 20:41:02 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

t_game *initialize_game(void)
{
    t_game *game = malloc(sizeof(t_game));
    if (game == NULL) {
        // handle allocation failure
        return NULL;
    }
    game->mlx = NULL;
    game->mlx_win = NULL;
	game->w_width = 1600;
	game->w_height = 800;
	game->raw = NULL;
   // game->walls = NULL;
//	game->walls = malloc(sizeof(t_bound) * 200);
    game->num_walls = 0;
	game->player.pos.x = 100;
	game->player.pos.y = 100;
	game->player.rot = 0;
	game->player.rb = 0;
	game->player.lb = 0;
	game->player.ub = 0;
	game->player.db = 0;

	game->keys.U_KEY_DOWN = 0;
	game->keys.D_KEY_DOWN = 0;
	game->keys.L_KEY_DOWN = 0;
	game->keys.R_KEY_DOWN = 0;
	game->keys.SH_KEY_DOWN = 0;
	game->keys.L_ROT_KEY_DOWN = 0;
	game->keys.R_ROT_KEY_DOWN = 0;

	return game;
} 

