/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:12:21 by ivanderw          #+#    #+#             */
/*   Updated: 2023/10/06 13:06:40 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

# include "libraries.h"
# include "draw.h"
# include "initialize.h"
# include "frame_refresh.h"

 void	c3d_player_cast(t_game *game);
float	get_raylength(t_ray ray, t_point end);
t_point	*ray_cast(t_bound *current_wall, t_ray *this_ray);
int		retrieve_colour(void *img, int x, int y);
void	c3d_draw_projection(t_game *game, float raylength, int i, int ray_x,
		int ray_y, t_bound *closest_wall);

#endif
