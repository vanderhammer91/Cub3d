/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bounds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 14:11:07 by ivanderw          #+#    #+#             */
/*   Updated: 2023/09/23 22:59:28 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"


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

void add_bound(t_game *game, float s_x, float s_y, float e_x, float e_y) 
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
	if (new_bound->end.y > new_bound->start.y)
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
void add_bound(t_game *game, float s_x, float s_y, float e_x, float e_y) 
{
  //  printf("number of walls we can fit: %zu\n", get_array_capacity(game->walls));
	t_bound* new_bound = malloc(sizeof(t_bound));
    if (new_bound == NULL) {
        free_bounds(*game->walls);
        free(*game->walls);
        *game->walls = NULL;
        return;
    }
    new_bound->start.x = s_x;
    new_bound->start.y = s_y;
    new_bound->end.x = e_x;
    new_bound->end.y = e_y;
    new_bound->next = NULL;

    if (game->num_walls > 0) {
        game->walls[game->num_walls-1]->next = new_bound;
    }
    game->walls[game->num_walls] = new_bound;
    game->num_walls++;
}
*/
/*
int	c3d_malloc_wall_bounds(t_game *game)
{
	int	i;
	int	j;
	int	map_height;
	int	map_width;
	int count;

	i = 0;
	count = 0;
	map_height = get_mapheight(game);
	map_width = ft_strlen(game->raw[i]);
	printf("map width here is: %d\n", map_width);
	while (game->raw[i])
	{
		j = 0;
		while (game->raw[i][j])
		{
			if (game->raw[i][j] == '1')
			{
				if ((i - 1) > -1 && game->raw[i - 1][j] == '0')
					count++;
				if ((j + 1) < (map_width - 1) && game->raw[i][j + 1] == '0')
					count++;
				if ((i + 1) < map_height && game->raw[i + 1][j] == '0')
					count++;
				if ((j - 1) > -1 && game->raw[i][j - 1] == '0')
					count++;		
			}
			else if (game->raw[i][j] == '0')
			{
			}
			//	rect(game->img, i * 80, j * 80, 79, 79, 0xFFFFFF);
			j++;
		}	
		i++;
	}
//	printf("there are %d bounds on this map.\n", count);
//	game->num_walls = count;
//	game->walls = malloc(sizeof(t_bound) * (count));
	return (0);
}
*/

int	c3d_set_wall_bounds(t_game *game)
{
	game->walls = malloc(sizeof(t_bound) * 200);
	game->num_walls = 0;
	int	i;
	int	j;
	int	m = 80;
	int	map_height;
	int	map_width;
	int count;
	int s_x, s_y, e_x, e_y;

	count = 0;
	i = 0;
	map_height = get_mapheight(game);
	map_width = ft_strlen(game->raw[i]) - 1;
	printf("map width here is: %d\n", map_width);

	while (i < map_height)
	{
		j = 0;
		// while (game->raw[i][j])
		while (j < map_width)
		{
			if (game->raw[i][j] == '1')
			{
				if ((i - 1) > -1 && game->raw[i - 1][j] == '0')
				{
					
					s_x = (j + 1) * m;
					s_y = i * m;
					e_x = j * m;
					e_y = i * m;
					add_bound(game, s_x, s_y, e_x, e_y);	
				}	
				if ((j + 1) < map_width-1 && game->raw[i][j + 1] == '0')
				{
					
					s_x = (j + 1) * m;
					s_y = (i + 1) * m;
					e_x = (j + 1) * m;
					e_y = i * m;
					add_bound(game, s_x, s_y, e_x, e_y);	
				}
				
				if ((i + 1) < map_height && game->raw[i + 1][j] == '0')
				{
					s_x = j * m;
					s_y = (i + 1) * m;
					e_x = (j + 1) * m;
					e_y = (i + 1) * m;
					add_bound(game, s_x, s_y, e_x, e_y);
				}
				
				if ((j - 1) > -1 && game->raw[i][j - 1] == '0')
				{	
					s_x = j * m;
					s_y = i * m;
					e_x = j * m;
					e_y = (i + 1) * m;
					add_bound(game, s_x, s_y, e_x, e_y);
				}
				
			}
			else if (game->raw[i][j] == '0')
			{
			}
			//	rect(game->img, i * 80, j * 80, 79, 79, 0xFFFFFF);
			
			j++;
		}	
		i++;
		
	}

//	c3d_set_bounds(game);
	//GREEN BOIZ
/*	
	add_bound(game, 400, 240, 320, 240);
	add_bound(game, 160, 320, 80, 320);
	add_bound(game, 320, 320, 240, 320);
	add_bound(game, 480, 320, 400, 320);
	add_bound(game, 640, 320, 560, 320);
	add_bound(game, 720, 320, 640, 320);
	add_bound(game, 160, 720, 80, 720);
	add_bound(game, 240, 720, 160, 720);
	add_bound(game, 320, 720, 240, 720);
	add_bound(game, 400, 720, 320, 720);
	add_bound(game, 480, 720, 400, 720);
	add_bound(game, 560, 720, 480, 720);
	add_bound(game, 640, 720, 560, 720);
	add_bound(game, 720, 720, 640, 720);
*/
	
	//blue boiz.
/*	
	add_bound(game, 80, 160, 80, 80);
	add_bound(game, 400, 160, 400, 80);
	add_bound(game, 80, 240, 80, 160);
	add_bound(game, 80, 320, 80, 240);
	add_bound(game, 400, 320, 400, 240);
	add_bound(game, 160, 400, 160, 320);
	add_bound(game, 480, 400, 480, 320);
	add_bound(game, 80, 480, 80, 400);
	add_bound(game, 400, 480, 400, 400);
	add_bound(game, 80, 560, 80, 480);
	add_bound(game, 400, 560, 400, 480);
	add_bound(game, 80, 640, 80, 560);
	add_bound(game, 400, 640, 400, 560);
	add_bound(game, 80, 720, 80, 640);
*/

	/*
	//red boiz.
	add_bound(game, 80, 80, 160, 80);
	add_bound(game, 160, 80, 240, 80);
	add_bound(game, 240, 80, 320, 80);
	add_bound(game, 400, 80, 480, 80);
	add_bound(game, 480, 80, 560, 80);
	add_bound(game, 560, 80, 640, 80);	
	add_bound(game, 640, 80, 720, 80);
	add_bound(game, 320, 160, 400, 160);
	add_bound(game, 80, 400, 160, 400);
	add_bound(game, 240, 400, 320, 400);
	add_bound(game, 400, 400, 480, 400);
	add_bound(game, 560, 400, 640, 400);
	add_bound(game, 640, 400, 720, 400);
	add_bound(game, 320, 640, 400, 640);
*/

	//Teal BOIZ?
/*
	add_bound(game, 320, 80, 320, 160);
	add_bound(game, 720, 80, 720, 160);
	add_bound(game, 720, 160, 720, 240);
	add_bound(game, 320, 240, 320, 320);
	add_bound(game, 720, 240, 720, 320);
	add_bound(game, 240, 320, 240, 400);
	add_bound(game, 560, 320, 560, 400);
	add_bound(game, 320, 400, 320, 480);
	add_bound(game, 720, 400, 720, 480);
	add_bound(game, 320, 480, 320, 560);
	add_bound(game, 720, 480, 720, 560);
	add_bound(game, 320, 560, 320, 640);
	add_bound(game, 720, 560, 720, 640);
	add_bound(game, 720, 640, 720, 720);
*/
	return (0);
}


