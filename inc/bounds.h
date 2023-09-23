/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bounds.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 13:50:41 by ivanderw          #+#    #+#             */
/*   Updated: 2023/09/22 14:57:03 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOUNDS_H
# define BOUNDS_H

# include "libraries.h"

void 	free_bounds(t_bound* head);
//void	add_bound(t_game *game, float s_x, float s_y, float e_x, float e_y);
void 	print_bounds(t_bound *head);
void	c3d_draw_bounds(t_game *game, void *img);

#endif
