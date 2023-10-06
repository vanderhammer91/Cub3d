/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 10:24:47 by ivanderw          #+#    #+#             */
/*   Updated: 2023/10/06 16:01:58 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

void	img_pixel_put(void *img, int x, int y, int color)
{
	char	*dst;
	int		bpp;
	int		size_line;
	int		endian;

	if (x < 0 || y < 0 || x >= 2000 || y >= 1000)
		return ;
	dst = mlx_get_data_addr(img, &bpp, &size_line, &endian);
	*(unsigned int *)(dst + y * size_line + x * bpp / 8) = color;
}

void	rect(void *img, t_point *start, t_point *end, int colour)
{
	int	i;
	int	j;

	i = 0;
	while (i < end->x)
	{
		j = 0;
		while (j < end->y)
		{
			img_pixel_put(img, start->x + i, start->y + j, colour);
			j++;
		}
		i++;
	}
}

void	draw_square(void *img, t_point p, int length, int color)
{
	t_point	top_left;
	t_point	top_right;
	t_point	bottom_left;
	t_point	bottom_right;

	top_left = p;
	top_right.x = p.x + length;
	top_right.y = p.y;
	bottom_left.x = p.x;
	bottom_left.y = p.y + length;
	bottom_right.x = p.x + length;
	bottom_right.y = p.y + length;
	line(img, top_left, top_right, color);
	line(img, top_right, bottom_right, color);
	line(img, bottom_right, bottom_left, color);
	line(img, bottom_left, top_left, color);
}
