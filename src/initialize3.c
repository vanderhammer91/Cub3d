/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 19:55:34 by ivanderw          #+#    #+#             */
/*   Updated: 2023/10/10 16:17:26 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "initialize.h"

void	c3d_add_southbound(t_game *game, int i, int j)
{
	t_bvertices	bv;	

	bv.s_x = (j + 1) * 64;
	bv.s_y = i * 64;
	bv.e_x = j * 64;
	bv.e_y = i * 64;
	add_bound(game, bv, SOUTH);
}

void	c3d_add_eastbound(t_game *game, int i, int j)
{
	t_bvertices	bv;	

	bv.s_x = j * 64;
	bv.s_y = i * 64;
	bv.e_x = j * 64;
	bv.e_y = (i + 1) * 64;
	add_bound(game, bv, EAST);
}
