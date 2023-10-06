/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_refresh.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 10:20:29 by ivanderw          #+#    #+#             */
/*   Updated: 2023/10/06 12:58:54 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRAME_REFRESH_H
# define FRAME_REFRESH_H

# include "libraries.h"
# include "draw.h"
# include "box_collider.h"
# include "raycast.h"
# include "definitions.h"

double get_safe_angle(double angle);
int	frame_refresh(t_game *game);

#endif
