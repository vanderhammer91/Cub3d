/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 10:24:47 by ivanderw          #+#    #+#             */
/*   Updated: 2023/09/20 14:46:53 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

void img_pixel_put(void *img, int x, int y, int color)
{
    char    *dst;
    int     bpp;
    int     size_line;
    int     endian;
	
    if (x < 0 || y < 0 || x >= 1600 || y >= 800)
        return;

    dst = mlx_get_data_addr(img, &bpp, &size_line, &endian);
    *(unsigned int*)(dst + y * size_line + x * bpp / 8) = color;
}

void rect(void *img, int x, int y, int width, int height, int color)
{
    int i, j;

    for (i = 0; i < width; i++) {
        for (j = 0; j < height; j++) {
            img_pixel_put(img, x + i, y + j, color);
        }
    }
}

void circle(void *img, int xc, int yc, int r, int color)
{
	int	x;
	int	y;
	int	d;

	x = 0, y = r;
	d = 3 - 2 * r;
    while (y >= x) {
        img_pixel_put(img, xc + x, yc + y, color);
        img_pixel_put(img, xc - x, yc + y, color);
        img_pixel_put(img, xc + x, yc - y, color);
        img_pixel_put(img, xc - x, yc - y, color);
        img_pixel_put(img, xc + y, yc + x, color);
        img_pixel_put(img, xc - y, yc + x, color);
        img_pixel_put(img, xc + y, yc - x, color);
        img_pixel_put(img, xc - y, yc - x, color);
        x++;
        if (d > 0) {
            y--;
            d = d + 4 * (x - y) + 10;
        } else {
            d = d + 4 * x + 6;
        }
    }
}

void filled_circle(void *img, int xc, int yc, int r, int color)
{
	int	x;
	int	y;

	for (x = xc - r; x <= xc + r; x++) {
		for (y = yc - r; y <= yc + r; y++) {
			if ((x - xc) * (x - xc) + (y - yc) * (y - yc) <= r * r)
				img_pixel_put(img, x, y, color);
		}
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

    while (1) {
       // img_pixel_put(img, x1, y1, color);

	    // Draw a pixel at (x1, y1) with the specified color
        for (int i = -thickness / 2; i <= thickness / 2; i++) {
            for (int j = -thickness / 2; j <= thickness / 2; j++) {
                img_pixel_put(img, x1 + i, y1 + j, color);
            }
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

