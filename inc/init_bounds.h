/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bounds.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 11:04:58 by ivanderw          #+#    #+#             */
/*   Updated: 2023/10/05 18:50:36 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_BOUNDS_H
# define INIT_BOUNDS_H

# include "libraries.h"
# include "bounds.h"
# include "raw_utils.h"
# include "init_player.h"
# include "parse.h"
 
t_game *initialize_game(t_parsed_data *d);
void	c3d_set_bounds(t_game *game);
void	c3d_free_bounds(t_game *game);
//int		c3d_malloc_wall_bounds(t_game *game);
int	c3d_set_wall_bounds(t_game *game);
void	c3d_print_bounds(t_game *game);
//void	c3d_remove_bound(t_game *game, t_bound *closest_wall);
void	c3d_remove_bound(t_game *game, int bound_index);
#endif
