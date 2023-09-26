/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 15:20:54 by ivanderw          #+#    #+#             */
/*   Updated: 2023/09/26 15:23:08 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_PLAYER_H
# define INIT_PLAYER_H

# include "libraries.h"

int		is_player_char(char c);
void	c3d_set_player_rot(t_game *game, char p_dir);
int		c3d_set_player_pos(t_game *game);

#endif
