/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:01:26 by ivanderw          #+#    #+#             */
/*   Updated: 2023/10/06 16:06:00 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

void	line_init_vars(t_line *line, t_point a, t_point b)
{
	line->x1 = round(a.x);
	line->y1 = round(a.y);
	line->x2 = round(b.x);
	line->y2 = round(b.y);
	line->dx = abs(line->x2 - line->x1);
	line->dy = abs(line->y2 - line->y1);
	line->err = line->dx - line->dy;
	if (line->x1 < line->x2)
	{
		line->sx = 1;
	}
	else
	{
		line->sx = -1;
	}
	if (line->y1 < line->y2)
	{
		line->sy = 1;
	}
	else
	{
		line->sy = -1;
	}
}

void	line_it(t_line *line)
{
	line->e2 = 2 * line->err;
	if (line->e2 > -line->dy)
	{
		line->err -= line->dy;
		line->x1 += line->sx;
	}
	if (line->e2 < line->dx)
	{
		line->err += line->dx;
		line->y1 += line->sy;
	}
}

void	line(void *img, t_point a, t_point b, int color)
{
	t_line	line;
	int		i;
	int		j;

	line_init_vars(&line, a, b);
	while (1)
	{
		i = -1 / 2;
		while (i <= (1 / 2))
		{
			j = -1 / 2;
			while (j <= (1 / 2))
				img_pixel_put(img, line.x1 + i, line.y1 + j++, color);
			i++;
		}
		if (line.x1 == line.x2 && line.y1 == line.y2)
			break ;
		line_it(&line);
	}
}
