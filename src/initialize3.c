/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:23:16 by ivanderw          #+#    #+#             */
/*   Updated: 2023/10/09 14:20:03 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "initialize.h"



int	c3d_set_wall_bounds(t_game *game)
{
	int	i;
	int	j;
	int count;
	t_bvertices bv;

	count = 0;
	i = 0;
	game->walls = malloc(sizeof(t_bound) * 200);
	game->num_walls = 0;
	game->map_height = get_mapheight(game);
	game->map_width = ft_strlen(game->raw[i]) - 1;
	while (i < game->map_height)
	{
		j = 0;
		while (j <= game->map_width)
		{
			if (game->raw[i][j] == '1')
			{
				if ((i - 1) > -1 && (is_space_char(game->raw[i - 1][j]) || is_player_char(game->raw[i - 1][j])))
				{	
					bv.s_x = (j + 1) * 64;
					bv.s_y = i * 64;
					bv.e_x = j * 64;
					bv.e_y = i * 64;
					add_bound(game, bv, SOUTH);	
				}	
				if ((j + 1) < game->map_width-1 && (is_space_char(game->raw[i][j + 1]) || is_player_char(game->raw[i][j + 1])))
				{	
					bv.s_x = (j + 1) * 64;
					bv.s_y = (i + 1) * 64;
					bv.e_x = (j + 1) * 64;
					bv.e_y = i * 64;
					add_bound(game, bv, EAST);	
				}
				if ((i + 1) < game->map_height && (is_space_char(game->raw[i + 1][j]) || is_player_char(game->raw[i + 1][j])))
				{
					bv.s_x = j * 64;
					bv.s_y = (i + 1) * 64;
					bv.e_x = (j + 1) * 64;
					bv.e_y = (i + 1) * 64;
					add_bound(game, bv, NORTH);	
				}
				
				if ((j - 1) > -1 && (is_space_char(game->raw[i][j - 1]) || is_player_char(game->raw[i][j - 1])))
				{	
					bv.s_x = j * 64;
					bv.s_y = i * 64;
					bv.e_x = j * 64;
					bv.e_y = (i + 1) * 64;
					add_bound(game, bv, WEST);	
				}	
			}
			else if (game->raw[i][j] == '2' || game->raw[i][j] == '4')
			{
					if (game->raw[i][j-1] == '1' && game->raw[i][j + 1] == '1')
					{
						bv.s_x = j * 64;
						bv.s_y = (i + 0.5) * 64;
						bv.e_x = (j + 1) * 64;
						bv.e_y = (i + 0.5) * 64;
						if (game->raw[i][j] == '2')
							add_bound(game, bv, DOOR);	
						else
							add_bound(game, bv, EXIT);	
					}
					else if (game->raw[i - 1][j] == '1' && game->raw[i + 1][j] == '1')
					{
						bv.s_x = (j + 0.5) * 64;
						bv.s_y = i * 64;
						bv.e_x = (j + 0.5) * 64;
						bv.e_y = (i + 1) * 64;
						if (game->raw[i][j] == '2')
							add_bound(game, bv, DOOR);	
						else
							add_bound(game, bv, EXIT);
					}
			}
			else if (game->raw[i][j] == '5')
			{
				bv.s_x = (j - 2) * 64;
				bv.s_y = (i + 0.1) * 64;
				bv.e_x = (j + 1) * 64;
				bv.e_y = (i + 0.1) * 64;
				add_bound(game, bv, AD);
			}
			else if (game->raw[i][j] == 'X')
			{
			//	int os = 25;
				//top face.
				bv.s_x = ((j + 1) * 64) - 25 ;
				bv.s_y = ((i) * 64) + 25;
				bv.e_x = ((j) * 64) + 25;
				bv.e_y = ((i) * 64) + 25;
				add_bound(game, bv, SOUTH);

				//left face
				bv.s_x = ((j) * 64) + 25;
				bv.s_y = ((i) * 64) + 25;
				bv.e_x = ((j) * 64) + 25;
				bv.e_y = ((i + 1) * 64) - 25;
				add_bound(game, bv, EAST);

				//bot face.
				bv.s_x = ((j) * 64) + 25;
				bv.s_y = ((i + 1) * 64) - 25;
				bv.e_x = ((j + 1) * 64) - 25;
				bv.e_y = ((i + 1) * 64) - 25;
				add_bound(game, bv, NORTH);

				//right face
				bv.s_x = ((j + 1) * 64) - 25;
				bv.s_y = ((i + 1) * 64) - 25;
				bv.e_x = ((j + 1) * 64) - 25;
				bv.e_y = ((i) * 64) + 25;
				add_bound(game, bv, WEST);
			}			
			j++;
		}	
		i++;	
	}
	return (0);
}
