/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_refresh3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 17:46:29 by ivanderw          #+#    #+#             */
/*   Updated: 2023/10/06 17:53:26 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frame_refresh.h"

void	c3d_draw_minimap_border(t_game *game)
{
	t_point	new_start;
	t_point	new_end;

	set_point(&new_start, 0, 0);
	set_point(&new_end, 300, 300);
	rect(game->img, &new_start, &new_end, 0x0c212e);
	set_point(&new_start, 145, 145);
	set_point(&new_end, 10, 10);
	rect(game->img, &new_start, &new_end, 0x00FFFF);
}

void	c3d_draw_minimap(t_game *game, void *img)
{
	int		offbound;
	int		i;
	t_point	new_start;
	t_point	new_end;

	offbound = 300;
	c3d_draw_minimap_border(game);	
	i = 0;
	while (i < game->num_walls)
	{
		t_bound *wall = game->walls[i];
		new_start.x = (wall->start.x - game->player.pos.x + offbound) / 2;
		new_start.y = (wall->start.y - game->player.pos.y + offbound) / 2;
		new_end.x = (wall->end.x - game->player.pos.x + offbound) / 2;
		new_end.y = (wall->end.y - game->player.pos.y + offbound) / 2;
		if (new_start.x > offbound)
			new_start.x = offbound;
		if (new_start.y > offbound)
			new_start.y = offbound;
		if (new_end.x > offbound)
			new_end.x = offbound;
		if (new_end.y > offbound)
			new_end.y = offbound;
		if (wall->type != DOOR)
        	line(img, new_start, new_end, 0x0000FF);
		else
		{	
			if (wall->is_active)
				line(img, new_start, new_end, 0x00FFFF);
		}
		i++;
    }
	draw_dir_arrow(game);
	new_start.x = 0;
	new_start.y = 0;
	draw_square(img, new_start, 300, 0x00FFFF);
	new_start.x = 5;
	new_start.y = 5;
	draw_square(img, new_start, 290, 0x00FFFF);
}

