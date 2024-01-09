/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:33:41 by ivanderw          #+#    #+#             */
/*   Updated: 2023/10/10 16:08:42 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

void	c3d_draw_south_projection(t_game *game, t_projection *dp, t_param tp)
{
	dp->start_y = dp->y_offset - tp.raylength * 0.5;
	dp->ty = 0;
	dp->ty_step = 64.0 / (float)tp.raylength;
	dp->tx = (int)(tp.ray_x) % 64;
	dp->tx = 63 - dp->tx;
	while (dp->y < tp.raylength)
	{
		dp->pixel_colour = retrieve_colour(game->t_lib.south_texture, dp->tx,
				dp->ty);
		dp->pixel_colour = shade_pixel(dp->pixel_colour, tp.raylength);
		dp->start.x = dp->x_offset + tp.i * dp->cw;
		dp->start.y = dp->start_y + dp->y;
		dp->end.x = dp->cw;
		dp->end.y = 1;
		rect(game->img, &dp->start, &dp->end, dp->pixel_colour);
		dp->ty += dp->ty_step;
		if (dp->ty >= 64)
		{
			dp->ty = 63;
		}
		dp->y++;
	}
}

void	c3d_draw_north_projection(t_game *game, t_projection *dp, t_param tp)
{
	dp->start_y = dp->y_offset - tp.raylength * 0.5;
	dp->ty = 0;
	dp->ty_step = 64.0 / (float)tp.raylength;
	dp->tx = (int)(tp.ray_x) % 64;
	while (dp->y < tp.raylength)
	{
		dp->pixel_colour = retrieve_colour(game->t_lib.north_texture, dp->tx,
				dp->ty);
		dp->pixel_colour = shade_pixel(dp->pixel_colour, tp.raylength);
		dp->start.x = dp->x_offset + tp.i * dp->cw;
		dp->start.y = dp->start_y + dp->y;
		dp->end.x = dp->cw;
		dp->end.y = 1;
		rect(game->img, &dp->start, &dp->end, dp->pixel_colour);
		dp->ty += dp->ty_step;
		if (dp->ty >= 64)
		{
			dp->ty = 63;
		}
		dp->y++;
	}
}

void	c3d_draw_east_projection(t_game *game, t_projection *dp, t_param tp)
{
	dp->start_y = dp->y_offset - tp.raylength * 0.5;
	dp->ty = 0;
	dp->ty_step = 64.0 / (float)tp.raylength;
	dp->tx = (int)(tp.ray_y) % 64;
	while (dp->y < tp.raylength)
	{
		dp->pixel_colour = retrieve_colour(game->t_lib.east_texture, dp->tx,
				dp->ty);
		dp->pixel_colour = shade_pixel(dp->pixel_colour, tp.raylength);
		dp->start.x = dp->x_offset + tp.i * dp->cw;
		dp->start.y = dp->start_y + dp->y;
		dp->end.x = dp->cw;
		dp->end.y = 1;
		rect(game->img, &dp->start, &dp->end, dp->pixel_colour);
		dp->ty += dp->ty_step;
		if (dp->ty >= 64)
		{
			dp->ty = 63;
		}
		dp->y++;
	}
}

void	c3d_draw_west_projection(t_game *game, t_projection *dp, t_param tp)
{
	dp->start_y = dp->y_offset - tp.raylength * 0.5;
	dp->ty = 0;
	dp->ty_step = 64.0 / (float)tp.raylength;
	dp->tx = (int)(tp.ray_y) % 64;
	dp->tx = 63 - dp->tx;
	while (dp->y < tp.raylength)
	{
		dp->pixel_colour = retrieve_colour(game->t_lib.west_texture, dp->tx,
				dp->ty);
		dp->pixel_colour = shade_pixel(dp->pixel_colour, tp.raylength);
		dp->start.x = dp->x_offset + tp.i * dp->cw;
		dp->start.y = dp->start_y + dp->y;
		dp->end.x = dp->cw;
		dp->end.y = 1;
		rect(game->img, &dp->start, &dp->end, dp->pixel_colour);
		dp->ty += dp->ty_step;
		if (dp->ty >= 64)
		{
			dp->ty = 63;
		}
		dp->y++;
	}
}

void	c3d_draw_projection(t_game *game, t_param tp, t_bound *closest_wall)
{
	t_projection	dp;

	dp.x_offset = 0;
	dp.y_offset = 500;
	dp.cw = 5;
	dp.y = 0;
	if (closest_wall->type == SOUTH)
		c3d_draw_south_projection(game, &dp, tp);
	else if (closest_wall->type == NORTH)
		c3d_draw_north_projection(game, &dp, tp);
	else if (closest_wall->type == EAST)
		c3d_draw_east_projection(game, &dp, tp);
	else if (closest_wall->type == WEST)
		c3d_draw_west_projection(game, &dp, tp);
}
