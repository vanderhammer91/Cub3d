/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 14:11:07 by ivanderw          #+#    #+#             */
/*   Updated: 2023/10/06 12:45:59 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "initialize.h"

/*
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
		printf("%d\n", game->walls[i]->type);
		i++;
	}
}
*/

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


void add_bound(t_game *game, float s_x, float s_y, float e_x, float e_y, enum e_wall_type wall_type ) 
{
	t_bound *new_bound = malloc(sizeof(t_bound));
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
	new_bound->type = wall_type;
	new_bound->texture = DEFAULT;
	new_bound->door_state = 0;
	new_bound->img_state = 0;
	if (wall_type == DOOR || wall_type == EXIT)
	{
		new_bound->is_active = 1;
		if (s_y != e_y)
			new_bound->is_vert = 1;
		else
			new_bound->is_vert = 0;
	}
    game->walls[game->num_walls] = new_bound;
    game->num_walls++;
}

void c3d_remove_bound(t_game *game, int bound_index) 
{
    if (bound_index < 0 || bound_index >= game->num_walls) 
    {
        printf("remove bound: index out of bounds!\n");
        return;
    } 
    free(game->walls[bound_index]);
    memmove(&game->walls[bound_index], &game->walls[bound_index + 1], (game->num_walls - bound_index - 1) * sizeof(t_bound*));
    game->num_walls--;
}

int	is_space_char(char c)
{
	if (c == '0' || c == '2' || c == '3' || c == 'X' || c == '4' || c == '5')
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
	while (i < map_height)
	{
		j = 0;
		while (j <= map_width)
		{
			if (game->raw[i][j] == '1')
			{
				if ((i - 1) > -1 && (is_space_char(game->raw[i - 1][j]) || is_player_char(game->raw[i - 1][j])))
				{	
					s_x = (j + 1) * m;
					s_y = i * m;
					e_x = j * m;
					e_y = i * m;
					add_bound(game, s_x, s_y, e_x, e_y, SOUTH);	
				}	
				if ((j + 1) < map_width-1 && (is_space_char(game->raw[i][j + 1]) || is_player_char(game->raw[i][j + 1])))
				{	
					s_x = (j + 1) * m;
					s_y = (i + 1) * m;
					e_x = (j + 1) * m;
					e_y = i * m;
					add_bound(game, s_x, s_y, e_x, e_y, EAST);	
				}
				if ((i + 1) < map_height && (is_space_char(game->raw[i + 1][j]) || is_player_char(game->raw[i + 1][j])))
				{
					s_x = j * m;
					s_y = (i + 1) * m;
					e_x = (j + 1) * m;
					e_y = (i + 1) * m;
					add_bound(game, s_x, s_y, e_x, e_y, NORTH);
				}
				
				if ((j - 1) > -1 && (is_space_char(game->raw[i][j - 1]) || is_player_char(game->raw[i][j - 1])))
				{	
					s_x = j * m;
					s_y = i * m;
					e_x = j * m;
					e_y = (i + 1) * m;
					add_bound(game, s_x, s_y, e_x, e_y, WEST);
				}	
			}
			else if (game->raw[i][j] == '2' || game->raw[i][j] == '4')
			{
					if (game->raw[i][j-1] == '1' && game->raw[i][j + 1] == '1')
					{
						s_x = j * m;
						s_y = (i + 0.5) * m;
						e_x = (j + 1) * m;
						e_y = (i + 0.5) * m;
						if (game->raw[i][j] == '2')
							add_bound(game, s_x, s_y, e_x, e_y, DOOR);
						else
							add_bound(game, s_x, s_y, e_x, e_y, EXIT);
					}
					else if (game->raw[i - 1][j] == '1' && game->raw[i + 1][j] == '1')
					{
						s_x = (j + 0.5) * m;
						s_y = i * m;
						e_x = (j + 0.5) * m;
						e_y = (i + 1) * m;
						if (game->raw[i][j] == '2')
							add_bound(game, s_x, s_y, e_x, e_y, DOOR);
						else
							add_bound(game, s_x, s_y, e_x, e_y, EXIT);
					}
			}
			else if (game->raw[i][j] == '5')
			{
				s_x = (j - 2) * m;
				s_y = (i + 0.1) * m;
				e_x = (j + 1) * m;
				e_y = (i + 0.1) * m;
				add_bound(game, s_x, s_y, e_x, e_y, AD);
			}
			else if (game->raw[i][j] == 'X')
			{
				int os = 25;
				//top face.
				s_x = ((j + 1) * m) - os ;
				s_y = ((i) * m) + os;
				e_x = ((j) * m) + os;
				e_y = ((i) * m) + os;
				add_bound(game, s_x, s_y, e_x, e_y, SOUTH);

				//left face
				s_x = ((j) * m) + os;
				s_y = ((i) * m) + os;
				e_x = ((j) * m) + os;
				e_y = ((i + 1) * m) - os;
				add_bound(game, s_x, s_y, e_x, e_y, EAST);

				//bot face.
				s_x = ((j) * m) + os;
				s_y = ((i + 1) * m) - os;
				e_x = ((j + 1) * m) - os;
				e_y = ((i + 1) * m) - os;
				add_bound(game, s_x, s_y, e_x, e_y, NORTH);

				//right face
				s_x = ((j + 1) * m) - os;
				s_y = ((i + 1) * m) - os;
				e_x = ((j + 1) * m) - os;
				e_y = ((i) * m) + os;
				add_bound(game, s_x, s_y, e_x, e_y, WEST);
			}			
			j++;
		}	
		i++;	
	}
	return (0);
}


