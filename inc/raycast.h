/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:12:21 by ivanderw          #+#    #+#             */
/*   Updated: 2023/10/07 20:32:50 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

# include "libraries.h"
# include "draw.h"
# include "initialize.h"
# include "frame_refresh.h"

 void	c3d_player_cast(t_game *game);

/*		raycast1.c*/
t_point	*ray_cast(t_bound *current_wall, t_ray *this_ray);
float	get_raylength(t_ray ray, t_point end);
int		retrieve_colour(void *img, int x, int y);
int		shade_pixel(int pixel_colour, float raylength);

void	c3d_draw_projection(t_game *game, t_param para, t_bound *closest_wall);


/*		raycast3.c*/
void	c3d_draw_ad_projection(t_game *game, t_projection *dp, t_param tp);
void	c3d_draw_door_projection(t_game *game, t_projection *dp, t_param tp,
		t_bound *closest_wall);
void	c3d_draw_exit_projection(t_game *game, t_projection *dp, t_param tp,
		t_bound *closest_wall);

#endif
