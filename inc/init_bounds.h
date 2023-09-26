/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bounds.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 11:04:58 by ivanderw          #+#    #+#             */
/*   Updated: 2023/09/26 15:34:15 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_BOUNDS_H
# define INIT_BOUNDS_H

# include "libraries.h"
# include "bounds.h"
# include "raw_utils.h"
# include "init_player.h"
 
t_game	*initialize_game(void);
void	c3d_set_bounds(t_game *game);
void	c3d_free_bounds(t_game *game);
//int		c3d_malloc_wall_bounds(t_game *game);
int	c3d_set_wall_bounds(t_game *game);
void	c3d_print_bounds(t_game *game);

#endif
