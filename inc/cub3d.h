/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 15:41:56 by ivanderw          #+#    #+#             */
/*   Updated: 2023/10/05 17:22:19 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libraries.h"
# include "init_bounds.h"
# include "key_events.h"
# include "gen_utils.h"
# include "raycast.h"
# include "bounds.h"
# include "draw.h"
# include "frame_refresh.h"
# include "init_player.h"

# define W_HEIGHT 1000
# define W_WIDTH 1200

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

void	c3d_init_rays(t_game *game);

/*		map_utilies.c		*/
int		set_parse(char **argv);
void	print_parse(void);

/*		other_utilies.c		*/			
int	c3d_set_raw(char **argv, t_game *game);
void c3d_print_raw(t_game *game);
int	get_mapheight(t_game *game);

#endif
