/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_refresh.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 10:20:29 by ivanderw          #+#    #+#             */
/*   Updated: 2023/10/06 15:31:04 by ivanderw         ###   ########.fr       */
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
int	frame_refresh(t_game *game);

#endif
