/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 10:24:47 by ivanderw          #+#    #+#             */
/*   Updated: 2023/10/06 14:11:13 by ivanderw         ###   ########.fr       */
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

void	rect(void *img, int x, int y, int width, int height, int color)
{
	int	i;
	int	j;
	
	i = 0;
	while (i < width)
	{
		j = 0;
        for (j < height)
		{
            img_pixel_put(img, x + i, y + j, color);
			j++;
        }
		i++;
    }
}


void line(void *img, t_point a, t_point b, int color)
{	
	int	x1 = round(a.x);
	int	y1 = round(a.y);
	int	x2 = round(b.x);
	int y2 = round(b.y);
	int thickness = 1;
	int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;
	int	i;
	int	j;

    while (1) {	
		i = -thickness / 2;
		while (i <= (thickness / 2))
		{
			j = -thickness / 2;
			while (j <= (thickness / 2))
			{
				img_pixel_put(img, x1 + i, y1 + j, color);
				j++;
			}
			i++;
		}
        if (x1 == x2 && y1 == y2) {
            break;
        }
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

void draw_square(void *img, t_point p, int length, int color)
{
    t_point top_left = p;
    t_point top_right = {p.x + length, p.y};
    t_point bottom_left = {p.x, p.y + length};
    t_point bottom_right = {p.x + length, p.y + length};

    line(img, top_left, top_right, color);
    line(img, top_right, bottom_right, color);
    line(img, bottom_right, bottom_left, color);
    line(img, bottom_left, top_left, color);
}

