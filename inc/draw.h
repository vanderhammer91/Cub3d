/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 10:22:18 by ivanderw          #+#    #+#             */
/*   Updated: 2023/10/06 16:03:07 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# include "libraries.h"

/*		draw.c*/
void	img_pixel_put(void *img, int x, int y, int color);
t_point	*new_point(int x, int y);
void	rect(void *img, t_point *start, t_point *end, int colour);
void	draw_square(void *img, t_point p, int length, int color);

/*		draw1.c*/
void	line(void *img, t_point a, t_point b, int color);

#endif
