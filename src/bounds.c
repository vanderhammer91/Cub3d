/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bounds.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 13:44:26 by ivanderw          #+#    #+#             */
/*   Updated: 2023/10/02 20:44:16 by ivanderw         ###   ########.fr       */
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

/*
void print_bounds(t_bound *head)
{
    t_bound* current_wall = head;
    int i = 0;

    while (current_wall != NULL)
    {
        printf("bound [%d]:\n", i);
        printf("wall start pt: %f, %f \n", current_wall->start.x, current_wall->start.y);    
        printf("wall end pt: %f, %f \n", current_wall->end.x, current_wall->end.y);
        current_wall = current_wall->next;
        i++;
    }
}
*/
/*
void add_bound(t_game *game, float s_x, float s_y, float e_x, float e_y) 
{
//	printf("dbg1 ");
    t_bound* new_bound = malloc(sizeof(t_bound));
    if (new_bound == NULL) {
		printf("add bound: malloc failed!\n");
        free_bounds(*game->walls);
        free(*game->walls);
        *game->walls = NULL;
        return;
	}
//	printf("dbg2 ");
    new_bound->start.x = s_x;
    new_bound->start.y = s_y;
    new_bound->end.x = e_x;
    new_bound->end.y = e_y;
	new_bound->direction = UNSET;
    new_bound->next = NULL;

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
//	printf("dbg3 ");

   // size_t current_size = sizeof(t_bound*) * game->num_walls;
  //  size_t new_size = sizeof(t_bound*) * (game->num_walls + 1);
   // t_bound** new_walls = realloc(game->walls, new_size);
    //if (new_walls == NULL) {
//		printf("add bound: malloc 2 failed!\n");
  //      free_bounds(*game->walls);
    //    free(*game->walls);
      //  *game->walls = NULL;
      //  return;
    }
//	printf("dbg4 ");
	if (game->num_walls > 0) {
        game->walls[game->num_walls-1]->next = new_bound;
    }
//	printf("dbg5 ");
    game->walls = new_walls;
    game->walls[game->num_walls] = new_bound;
    game->num_walls++;
//	printf("dbg6\n");
}
*/

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

void c3d_draw_bounds(t_game *game, void *img)
{
    for (int i = 0; i < game->num_walls; i++) {
    //    printf("printing wall[%d]: ", i);
		t_bound *wall = game->walls[i];

        // Call the line function to draw the wall
        line(img, wall->start, wall->end, 0xFF0000);
    }
}

