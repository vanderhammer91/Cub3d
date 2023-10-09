/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:19:22 by ivanderw          #+#    #+#             */
/*   Updated: 2023/10/09 17:09:43 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

void	ray_cast_init(t_bound *current_wall, t_ray *this_ray,
		t_cast_handler *tc)
{
	tc->radians = this_ray->rot * M_PI / 180.0;
	tc->x1 = current_wall->start.x;
	tc->y1 = current_wall->start.y;
	tc->x2 = current_wall->end.x;
	tc->y2 = current_wall->end.y;
	tc->x3 = this_ray->pos.x;
	tc->y3 = this_ray->pos.y;
	tc->x4 = this_ray->pos.x + cos(tc->radians);
	tc->y4 = this_ray->pos.y + sin(tc->radians);
	tc->denominator = (tc->x1 - tc->x2) * (tc->y3 - tc->y4) \
		- (tc->y1 - tc->y2) * (tc->x3 - tc->x4);
}

t_point	*ray_cast(t_bound *current_wall, t_ray *this_ray)
{
	t_point			*pt;
	t_cast_handler	tc;
	if (!current_wall)
		return (NULL);

	ray_cast_init(current_wall, this_ray, &tc);
	if (tc.denominator != 0)
	{
		tc.t = ((tc.x1 - tc.x3) * (tc.y3 - tc.y4) - \
			(tc.y1 - tc.y3) * (tc.x3 - tc.x4)) / tc.denominator;
		tc.u = -((tc.x1 - tc.x2) * (tc.y1 - tc.y3) - \
			(tc.y1 - tc.y2) * (tc.x1 - tc.x3)) / tc.denominator;
		if (tc.t > 0 && tc.t < 1 && tc.u > 0)
		{
			pt = malloc(sizeof(t_point));
			if (!pt)
				return (printf("c3d_internal: raycast: failed malloc\n"), NULL);
			pt->x = tc.x1 + tc.t * (tc.x2 - tc.x1);
			pt->y = tc.y1 + tc.t * (tc.y2 - tc.y1);
			return (pt);
		}
	}
	return (NULL);
}

float	get_raylength(t_ray ray, t_point end)
{
	float	x_diff;
	float	y_diff;

	x_diff = end.x - ray.pos.x;
	y_diff = end.y - ray.pos.y;
	return (sqrt(x_diff * x_diff + y_diff * y_diff));
}

int	retrieve_colour(void *img, int x, int y)
{
	char	*data;
	int		bpp;
	int		size_line;
	int		endian;
	int		colour;

	data = mlx_get_data_addr(img, &bpp, &size_line, &endian);
	colour = *(int *)(data + ((x * bpp / 8) + (y * size_line)));
	return (colour);
}

int	shade_pixel(int pixel_colour, float raylength)
{
	float	shading;
	int		red;
	int		green;
	int		blue;
	int		shaded;

	shading = 0.005 * raylength;
	if (shading < 0)
		shading = 0;
	if (shading > 1)
		shading = 1;
	red = (pixel_colour >> 16) & 0xFF;
	green = (pixel_colour >> 8) & 0xFF;
	blue = pixel_colour & 0xFF;
	red = (int)(red * shading);
	green = (int)(green * shading);
	blue = (int)(blue * shading);
	shaded = (red << 16) | (green << 8) | blue;
	return (shaded);
}
