/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_refresh1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:07:44 by ivanderw          #+#    #+#             */
/*   Updated: 2023/10/10 15:06:11 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frame_refresh.h"

double	get_safe_angle(double angle)
{
	while (angle < 0)
		angle += 360;
	while (angle > 360)
		angle -= 360;
	return (angle);
}

void	set_point(t_point *point, int x, int y)
{
	point->x = x;
	point->y = y;
}

int	draw_dir_arrow(t_game *game)
{
	t_point		start;
	t_point		end;
	t_point		unit_vector;
	double		radians;
	double		radius;

	radians = game->player.rot * M_PI / 180.0;
	radius = 15;
	start.x = 150;
	start.y = 150;
	unit_vector.x = cos(radians) * radius;
	unit_vector.y = sin(radians) * radius;
	end.x = start.x + unit_vector.x;
	end.y = start.y + unit_vector.y;
	line(game->img, start, end, 0x00FFFF);
	return (0);
}
