/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 11:03:33 by ivanderw          #+#    #+#             */
/*   Updated: 2023/09/22 14:56:21 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEY_EVENTS_H
# define KEY_EVENTS_H

#include "libraries.h"
# include "gen_utils.h"

int	key_press(int keycode, t_game *game);
int key_release(int keycode, t_game *game);
int	mouse_move(int x, int y, t_game *game);

#endif
