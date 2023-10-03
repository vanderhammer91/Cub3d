/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bounds.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 13:44:26 by ivanderw          #+#    #+#             */
/*   Updated: 2023/10/03 17:35:41 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
//#include "bounds.h"


void free_bounds(t_bound* head)
{
    t_bound* current = head;
    while (current != NULL) {
        t_bound* temp = current;
        current = current->next;
        free(temp);
    }
}

void c3d_draw_bounds(t_game *game, void *img)
{
	int i;

	i = 0;
	while(i < game->num_walls)
	{
		t_bound *wall = game->walls[i];
        line(img, wall->start, wall->end, 0xFF0000);
		i++;
    }
}

