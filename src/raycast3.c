/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 20:20:54 by ivanderw          #+#    #+#             */
/*   Updated: 2023/10/10 15:02:31 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

void	c3d_draw_door_projection_init(t_game *game, t_projection *dp,
		t_param tp)
{
	dp->img_state = game->walls[game->cwi]->img_state;
	dp->start_y = dp->y_offset - tp.raylength * 0.5;
	dp->ty = 0;
	dp->ty_step = 128.0 / (float)tp.raylength;
}

void	c3d_draw_door_projection(t_game *game, t_projection *dp, t_param tp,
		t_bound *closest_wall)
{
	c3d_draw_door_projection_init(game, dp, tp);
	if (closest_wall->is_vert == 0)
		dp->tx = (int)(tp.ray_x) % 128;
	else
		dp->tx = (int)(tp.ray_y) % 128;
	while (dp->y < tp.raylength)
	{
		dp->pixel_colour = retrieve_colour(game->t_lib.door_texture, dp->tx * 2,
				dp->ty + dp->img_state * 128);
		dp->alpha = (dp->pixel_colour >> 24) & 0xFF;
		if (!dp->alpha)
		{
			dp->pixel_colour = shade_pixel(dp->pixel_colour, tp.raylength);
			dp->start.x = dp->x_offset + tp.i * dp->cw;
			dp->start.y = dp->start_y + dp->y;
			dp->end.x = dp->cw;
			dp->end.y = 1;
			rect(game->img, &dp->start, &dp->end, dp->pixel_colour);
		}
		dp->ty += dp->ty_step;
		if (dp->ty >= 128)
			dp->ty = 127;
		dp->y++;
	}
}

void	c3d_draw_exit_projection(t_game *game, t_projection *dp, t_param tp,
		t_bound *closest_wall)
{
	dp->img_state = game->walls[game->cwi]->img_state;
	dp->start_y = dp->y_offset - tp.raylength * 0.5;
	dp->ty = 0;
	dp->ty_step = 128.0 / (float)tp.raylength;
	if (closest_wall->is_vert == 0)
		dp->tx = (int)(tp.ray_x) % 128;
	else
		dp->tx = (int)(tp.ray_y) % 128;
	while (dp->y < tp.raylength)
	{
		dp->pixel_colour = retrieve_colour(game->t_lib.exit_texture, dp->tx * 2,
				dp->ty + dp->img_state * 128);
		dp->pixel_colour = shade_pixel(dp->pixel_colour, tp.raylength);
		dp->start.x = dp->x_offset + tp.i * dp->cw;
		dp->start.y = dp->start_y + dp->y;
		dp->end.x = dp->cw;
		dp->end.y = 1;
		rect(game->img, &dp->start, &dp->end, dp->pixel_colour);
		dp->ty += dp->ty_step;
		if (dp->ty >= 128)
		{
			dp->ty = 127;
		}
		dp->y++;
	}
}
