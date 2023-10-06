/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_refresh.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 10:20:29 by ivanderw          #+#    #+#             */
/*   Updated: 2023/10/06 20:29:49 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRAME_REFRESH_H
# define FRAME_REFRESH_H

# include "libraries.h"
# include "draw.h"
# include "box_collider.h"
# include "raycast.h"
# include "definitions.h"

void	set_point(t_point *point, int x, int y);
double	get_safe_angle(double angle);
int		frame_refresh(t_game *game);

/*		frame_refresh1.c*/
double	get_safe_angle(double angle);
void	set_point(t_point *point, int x, int y);
int		draw_dir_arrow(t_game *game);
void	c3d_draw_overlay(t_game *game);

/*		frame_refresh2.c*/
int		c3d_update_player_pos(t_game *game);

/*		frame_refresh3.c*/
void	c3d_draw_minimap(t_game *game);

/*		frame_refresh4.c*/
void	c3d_check_walls_call(t_game *game);
void	draw_gun_state(t_game *game, int gun_state, int x_off, int y_off);
void	c3d_check_gun_state(t_game *game);

/*		frame_refresh5.c*/
void	frame_refresh_title(t_game *game);

#endif
