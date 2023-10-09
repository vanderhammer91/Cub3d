/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 14:11:07 by ivanderw          #+#    #+#             */
/*   Updated: 2023/10/09 12:39:06 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "initialize.h"

void	c3d_free_bounds(t_game *game)
{
	int	i;

	i = 0;
	while (game->walls[i])
	{
		free(game->walls[i]);
		i++;
	}
}

void	init_bound(t_bound *new_bound, t_bvertices bv,
		enum e_wall_type wall_type)
{
	new_bound->start.x = bv.s_x;
	new_bound->start.y = bv.s_y;
	new_bound->end.x = bv.e_x;
	new_bound->end.y = bv.e_y;
	new_bound->type = wall_type;
	new_bound->texture = DEFAULT;
	new_bound->door_state = 0;
	new_bound->img_state = 0;
}

void	add_bound(t_game *game, t_bvertices bv, enum e_wall_type wall_type)
{
	t_bound	*new_bound;

	new_bound = malloc(sizeof(t_bound));
	if (new_bound == NULL)
	{
		printf("add bound: malloc failed!\n");
		free_bounds(*game->walls);
		free(*game->walls);
		*game->walls = NULL;
		return ;
	}
	init_bound(new_bound, bv, wall_type);
	if (wall_type == DOOR || wall_type == EXIT)
	{
		new_bound->is_active = 1;
		if (bv.s_y != bv.e_y)
			new_bound->is_vert = 1;
		else
			new_bound->is_vert = 0;
	}
	game->walls[game->num_walls] = new_bound;
	game->num_walls++;
}

void	c3d_remove_bound(t_game *game, int bound_index)
{
	if (bound_index < 0 || bound_index >= game->num_walls)
	{
		printf("remove bound: index out of bounds!\n");
		return ;
	}
	free(game->walls[bound_index]);
	memmove(&game->walls[bound_index], &game->walls[bound_index + 1],
		(game->num_walls - bound_index - 1) * sizeof(t_bound*));
	game->num_walls--;
}

int	is_space_char(char c)
{
	if (c == '0' || c == '2' || c == '3' || c == 'X' || c == '4' || c == '5')
		return (1);
	return (0);
}
