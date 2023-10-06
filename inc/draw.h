/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 10:22:18 by ivanderw          #+#    #+#             */
/*   Updated: 2023/10/06 14:37:20 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# include "libraries.h"

/*		draw.c*/
void	img_pixel_put(void *img, int x, int y, int color);
t_point	*new_point(int x, int y);
void	rect(void *img, t_point *start, t_point *end, int colour);


//void	rect(void *img, int x, int y, int width, int height, int color);
void	circle(void *img, int xc, int yc, int r, int color);
void	line(void *img, t_point a, t_point b, int color);
void	filled_circle(void *img, int xc, int yc, int r, int color);
void	draw_square(void *img, t_point p, int length, int color);

#endif
