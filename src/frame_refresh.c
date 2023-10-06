/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_refresh.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 10:18:51 by ivanderw          #+#    #+#             */
/*   Updated: 2023/10/06 21:03:56 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frame_refresh.h"

void	frame_refresh_exit(t_game *game)
{
	game->frame++;
	if (game->frame >= 80)
		ft_start_exit("YOU WIN!\n", game);
	mlx_clear_window(game->mlx, game->mlx_win);
	game->img = mlx_new_image(game->mlx, W_WIDTH, W_HEIGHT);
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->t_lib.exit_msg_texture,
		(W_WIDTH / 2) - (game->msg_width / 2), (W_HEIGHT / 2)
		- (game->msg_height / 2));
	mlx_destroy_image(game->mlx, game->img);
}

int	frame_refresh_main(t_game *game)
{
	game->frame++;
	if (game->frame >= 8)
		game->frame = 0;
	if (game->frame % 2 == 0)
	{
		game->ad_state++;
		c3d_check_walls_call(game);
		c3d_check_gun_state(game);
	}
	mlx_clear_window(game->mlx, game->mlx_win);
	game->img = mlx_new_image(game->mlx, 1400, 1000);
	c3d_update_player_pos(game);
	rect(game->img, &(t_point){0, 0}, &(t_point){1200, 500}, game->skycolour);
	rect(game->img, &(t_point){0, 500}, &(t_point){1200, 500},
		game->floorcolour);
	c3d_player_cast(game);
	rect(game->img, &(t_point){600, 540}, &(t_point){10, 10}, 0xFFFFFF);
	c3d_draw_minimap(game);
	test_hitrays(game);
	draw_gun_state(game, game->gun_state, 350, 475);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img, 0, 0);
	c3d_draw_overlay(game);
	mlx_destroy_image(game->mlx, game->img);
	return (0);
}

int	frame_refresh(t_game *game)
{
	if (game->game_state == 0)
		frame_refresh_title(game);
	else if (game->game_state == 1)
		frame_refresh_main(game);
	else if (game->game_state == 2)
		frame_refresh_exit(game);
	return (0);
}
