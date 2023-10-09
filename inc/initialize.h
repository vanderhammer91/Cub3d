/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 21:09:29 by ivanderw          #+#    #+#             */
/*   Updated: 2023/10/09 12:30:35 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INITIALIZE_H
# define INITIALIZE_H

# include "libraries.h"
# include "bounds.h"
# include "raw_utils.h"
# include "gen_utils.h"
# include "init_player.h"
# include "parse.h"

int		rgb_to_hex(int r, int g, int b);
t_game	*c3d_initialize_game(t_parsed_data *d);
void	c3d_initialize_key_states(t_game *game);
void	c3d_initialize_textures(t_game *game, t_parsed_data *d);
void	c3d_initialize_textures2(t_game *game);

void	c3d_set_bounds(t_game *game);
void	c3d_free_bounds(t_game *game);
int	c3d_set_wall_bounds(t_game *game);
void	c3d_print_bounds(t_game *game);
void	c3d_remove_bound(t_game *game, int bound_index);

void	c3d_free_bounds(t_game *game);
void	init_bound(t_bound *new_bound, t_bvertices bv, enum e_wall_type wall_type);
void	add_bound(t_game *game, t_bvertices bv, enum e_wall_type wall_type);
void	c3d_remove_bound(t_game *game, int bound_index);
int		is_space_char(char c);



#endif
