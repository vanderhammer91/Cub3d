/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 10:22:18 by ivanderw          #+#    #+#             */
/*   Updated: 2023/09/22 14:56:42 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# include "libraries.h"

/*		draw.c*/
void	img_pixel_put(void *img, int x, int y, int color);
void	rect(void *img, int x, int y, int width, int height, int color);
void	circle(void *img, int xc, int yc, int r, int color);
void	line(void *img, t_point a, t_point b, int color);
void	filled_circle(void *img, int xc, int yc, int r, int color);

#endif
