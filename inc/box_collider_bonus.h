/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box_collider_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 14:54:00 by ivanderw          #+#    #+#             */
/*   Updated: 2023/10/10 20:13:55 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOX_COLLIDER_BONUS_H
# define BOX_COLLIDER_BONUS_H

# include "libraries.h"
# include "draw.h"
# include "raycast_bonus.h"

int		test_right_hitray(t_game *game);
void	c3d_collider_check_right(t_game *game);
int		test_left_hitray(t_game *game);
void	c3d_collider_check_left(t_game *game);

int		test_up_hitray(t_game *game);
void	c3d_collider_check_up(t_game *game);
int		test_down_hitray(t_game *game);
void	c3d_collider_check_down(t_game *game);

void	test_hitrays(t_game *game);
#endif
