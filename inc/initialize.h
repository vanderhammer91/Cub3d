/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lxu <lxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 21:09:29 by ivanderw          #+#    #+#             */
/*   Updated: 2023/10/10 16:16:28 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INITIALIZE_H
# define INITIALIZE_H

# include "libraries.h"
# include "raw_utils.h"
# include "gen_utils.h"
# include "init_player.h"
# include "parse.h"

/*		initialize.c*/
int		rgb_to_hex(int r, int g, int b);
t_game	*c3d_initialize_game(t_parsed_data *d);
void	c3d_initialize_key_states(t_game *game);
void	c3d_initialize_textures(t_game *game, t_parsed_data *d);
void	c3d_initialize_textures2(t_game *game);

/*		initialize1.c*/
void	c3d_set_bounds(t_game *game);
void	c3d_free_bounds(t_game *game);
int		c3d_set_wall_bounds(t_game *game);
void	c3d_print_bounds(t_game *game);
void	c3d_remove_bound(t_game *game, int bound_index);

/*		initialize2.c*/
void	c3d_free_bounds(t_game *game);
void	init_bound(t_bound *new_bound, t_bvertices bv, \
		enum e_wall_type wall_type);
void	add_bound(t_game *game, t_bvertices bv, enum e_wall_type wall_type);
void	c3d_remove_bound(t_game *game, int bound_index);
int		is_space_char(char c);

/*		initialize2.c*/
void	c3d_add_northbound(t_game *game, int i, int j);
void	c3d_add_westbound(t_game *game, int i, int j);
int		c3d_set_wall_bounds(t_game *game);

/*		initialize3.c*/
void	c3d_add_southbound(t_game *game, int i, int j);
void	c3d_add_eastbound(t_game *game, int i, int j);

/*		initialize4.c*/
t_bound	**malloc_bounds(t_game *game);

#endif
