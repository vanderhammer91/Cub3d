/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bounds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 14:11:07 by ivanderw          #+#    #+#             */
/*   Updated: 2023/09/27 17:53:13 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init_bounds.h"

void	c3d_print_bounds(t_game *game)
{
	int	i;

	i = 0;
	while (game->walls[i])
	{
		 printf("bound [%d]:\n", i);
        	printf("wall start pt: %f, %f \n", game->walls[i]->start.x,
			game->walls[i]->start.y);    
        	printf("wall end pt: %f, %f \n", game->walls[i]->end.x,
			game->walls[i]->end.y);
		printf("%d\n", game->walls[i]->direction);
		i++;
	}
}

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


void add_bound(t_game *game, float s_x, float s_y, float e_x, float e_y, int wall_type) 
{
	t_bound *new_bound = malloc(sizeof(t_bound));
	t_bound *temp;
    if (new_bound == NULL)
	{
		printf("add bound: malloc failed!\n");
        	free_bounds(*game->walls);
        	free(*game->walls);
        	*game->walls = NULL;
        	return;
	} 
    new_bound->start.x = s_x;
    new_bound->start.y = s_y;
    new_bound->end.x = e_x;
    new_bound->end.y = e_y;
	new_bound->direction = UNSET;
	if (wall_type > 0)
	{
		new_bound->direction = DOOR;
		new_bound->is_active = 1;
	}
	else if (new_bound->end.y > new_bound->start.y)
		new_bound->direction = EAST;
	else if (new_bound->end.y < new_bound->start.y)
		new_bound->direction = WEST;
	else
	{
		if (new_bound->end.x > new_bound->start.x)
			new_bound->direction = NORTH;
		else
			new_bound->direction = SOUTH;
	}
	temp = game->walls[game->num_walls];
    	game->walls[game->num_walls] = new_bound;
	free(temp);
    	game->num_walls++;
}

/*
void	c3d_remove_bound(t_game *game, t_bound *closest_wall)
{
	(void)game;
	(void)closest_wall;
	printf("WE ARE CLOSE TO A DOOR YAY!\n");
}
*/
void c3d_remove_bound(t_game *game, int bound_index) 
{
    if (bound_index < 0 || bound_index >= game->num_walls) 
    {
        printf("remove bound: index out of bounds!\n");
        return;
    }
    
    free(game->walls[bound_index]);

    // Shift remaining elements
    memmove(&game->walls[bound_index], &game->walls[bound_index + 1], (game->num_walls - bound_index - 1) * sizeof(t_bound*));

    game->num_walls--;
}


int	is_space_char(char c)
{
	if (c == '0' || c == '2' || c == '3' )
		return (1);
	return (0);
}

int	c3d_set_wall_bounds(t_game *game)
{

	int	i;
	int	j;
	int	m = 64;
	int	map_height;
	int	map_width;
	int count;
	int s_x, s_y, e_x, e_y;

	count = 0;
	i = 0;
	game->walls = malloc(sizeof(t_bound) * 200);
	game->num_walls = 0;
	map_height = get_mapheight(game);
	map_width = ft_strlen(game->raw[i]) - 1;
	printf("map width here is: %d\n", map_width);

	while (i < map_height)
	{
		j = 0;
		while (j < map_width)
		{
			if (game->raw[i][j] == '1')
			{
				if ((i - 1) > -1 && (is_space_char(game->raw[i - 1][j]) || is_player_char(game->raw[i - 1][j])))
				{	
					s_x = (j + 1) * m;
					s_y = i * m;
					e_x = j * m;
					e_y = i * m;
					add_bound(game, s_x, s_y, e_x, e_y, 0);	
				}	
				if ((j + 1) < map_width-1 && (is_space_char(game->raw[i][j + 1]) || is_player_char(game->raw[i][j + 1])))
				{	
					s_x = (j + 1) * m;
					s_y = (i + 1) * m;
					e_x = (j + 1) * m;
					e_y = i * m;
					add_bound(game, s_x, s_y, e_x, e_y, 0);	
				}
				if ((i + 1) < map_height && (is_space_char(game->raw[i + 1][j]) || is_player_char(game->raw[i + 1][j])))
				{
					s_x = j * m;
					s_y = (i + 1) * m;
					e_x = (j + 1) * m;
					e_y = (i + 1) * m;
					add_bound(game, s_x, s_y, e_x, e_y, 0);
				}
				
				if ((j - 1) > -1 && (is_space_char(game->raw[i][j - 1]) || is_player_char(game->raw[i][j - 1])))
				{	
					s_x = j * m;
					s_y = i * m;
					e_x = j * m;
					e_y = (i + 1) * m;
					add_bound(game, s_x, s_y, e_x, e_y, 0);
				}
				
				
			}
			else if (game->raw[i][j] == '2')
			{
					s_x = j * m;
					s_y = (i + 0.5) * m;
					e_x = (j + 1) * m;
					e_y = (i + 0.5) * m;
					add_bound(game, s_x, s_y, e_x, e_y, 1);
			}			
			j++;
		}	
		i++;
		
	}
	return (0);
}


