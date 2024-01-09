/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_refresh.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 10:18:51 by ivanderw          #+#    #+#             */
/*   Updated: 2023/10/10 16:02:07 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frame_refresh.h"

int	frame_refresh_main(t_game *game)
{
	mlx_clear_window(game->mlx, game->mlx_win);
	game->img = mlx_new_image(game->mlx, 1400, 1000);
	c3d_update_player_pos(game);
	rect(game->img, &(t_point){0, 0}, &(t_point){1200, 500}, game->skycolour);
	rect(game->img, &(t_point){0, 500}, &(t_point){1200, 500},
		game->floorcolour);
	c3d_player_cast(game);
	rect(game->img, &(t_point){600, 540}, &(t_point){10, 10}, 0xFFFFFF);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img, 0, 0);
	mlx_destroy_image(game->mlx, game->img);
	return (0);
}

int	frame_refresh(t_game *game)
{
	frame_refresh_main(game);
	return (0);
}
