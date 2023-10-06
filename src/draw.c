/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 10:24:47 by ivanderw          #+#    #+#             */
/*   Updated: 2023/10/06 15:23:55 by ivanderw         ###   ########.fr       */
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
/*
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
*/

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

typedef struct s_line
{
	int	x1;
	int	y1;
	int	x2;
	int y2;
	int dx;
    int dy;
    int sx;
    int sy;
    int err;
} t_line;

void	line(void *img, t_point a, t_point b, int color)
{
	t_line	line;
	int	i;
	int	j;

	line.x1 = round(a.x);
	line.y1 = round(a.y);
	line.x2 = round(b.x);
	line.y2 = round(b.y);
	line.dx = abs(line.x2 - line.x1);
    line.dy = abs(line.y2 - line.y1);
    line.sx = (line.x1 < line.x2) ? 1 : -1;
    line.sy = (line.y1 < line.y2) ? 1 : -1;
    line.err = line.dx - line.dy;
    while (1)
	{	
		i = -1 / 2;
		while (i <= (1 / 2))
		{
			j = -1 / 2;
			while (j <= (1 / 2))
			{
				img_pixel_put(img, line.x1 + i, line.y1 + j, color);
				j++;
			}
			i++;
		}
        if (line.x1 == line.x2 && line.y1 == line.y2)
		{
            break;
        }
        int e2 = 2 * line.err;
        if (e2 > -line.dy)
		{
            line.err -= line.dy;
            line.x1 += line.sx;
        }
        if (e2 < line.dx)
		{
            line.err += line.dx;
			line.y1 += line.sy;
            //a.y = round(a.y + sy);
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

