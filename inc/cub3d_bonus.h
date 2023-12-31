/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 15:41:56 by ivanderw          #+#    #+#             */
/*   Updated: 2023/10/10 18:50:32 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "libraries.h"
# include "initialize_bonus.h"
# include "key_events.h"
# include "gen_utils.h"
# include "raycast_bonus.h"
# include "draw.h"
# include "frame_refresh_bonus.h"
# include "init_player.h"
# include "definitions.h"

void	c3d_init_rays(t_game *game);

/*		map_utilies.c		*/
int		set_parse(char **argv);
void	print_parse(void);

/*		other_utilies.c		*/			
int		c3d_set_raw(char **argv, t_game *game);
void	c3d_print_raw(t_game *game);
int		get_mapheight(t_game *game);

#endif
