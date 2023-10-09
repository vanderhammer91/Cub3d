/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:23:16 by ivanderw          #+#    #+#             */
/*   Updated: 2023/10/09 12:43:22 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "initialize.h"

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
					add_bound(game, (t_bvertices){s_x, s_y, e_x, e_y}, SOUTH);	
				}	
				if ((j + 1) < map_width-1 && (is_space_char(game->raw[i][j + 1]) || is_player_char(game->raw[i][j + 1])))
				{	
					s_x = (j + 1) * m;
					s_y = (i + 1) * m;
					e_x = (j + 1) * m;
					e_y = i * m;
					add_bound(game, (t_bvertices){s_x, s_y, e_x, e_y}, EAST);	
				}
				if ((i + 1) < map_height && (is_space_char(game->raw[i + 1][j]) || is_player_char(game->raw[i + 1][j])))
				{
					s_x = j * m;
					s_y = (i + 1) * m;
					e_x = (j + 1) * m;
					e_y = (i + 1) * m;
					add_bound(game, (t_bvertices){s_x, s_y, e_x, e_y}, NORTH);	
				}
				
				if ((j - 1) > -1 && (is_space_char(game->raw[i][j - 1]) || is_player_char(game->raw[i][j - 1])))
				{	
					s_x = j * m;
					s_y = i * m;
					e_x = j * m;
					e_y = (i + 1) * m;
					add_bound(game, (t_bvertices){s_x, s_y, e_x, e_y}, WEST);	
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
							add_bound(game, (t_bvertices){s_x, s_y, e_x, e_y}, DOOR);	
						else
							add_bound(game, (t_bvertices){s_x, s_y, e_x, e_y}, EXIT);	
					}
					else if (game->raw[i - 1][j] == '1' && game->raw[i + 1][j] == '1')
					{
						s_x = (j + 0.5) * m;
						s_y = i * m;
						e_x = (j + 0.5) * m;
						e_y = (i + 1) * m;
						if (game->raw[i][j] == '2')
							add_bound(game, (t_bvertices){s_x, s_y, e_x, e_y}, DOOR);	
						else
							add_bound(game, (t_bvertices){s_x, s_y, e_x, e_y}, EXIT);
					}
			}
			else if (game->raw[i][j] == '5')
			{
				s_x = (j - 2) * m;
				s_y = (i + 0.1) * m;
				e_x = (j + 1) * m;
				e_y = (i + 0.1) * m;
				add_bound(game, (t_bvertices){s_x, s_y, e_x, e_y}, AD);
			}
			else if (game->raw[i][j] == 'X')
			{
				int os = 25;
				//top face.
				s_x = ((j + 1) * m) - os ;
				s_y = ((i) * m) + os;
				e_x = ((j) * m) + os;
				e_y = ((i) * m) + os;
				add_bound(game, (t_bvertices){s_x, s_y, e_x, e_y}, SOUTH);

				//left face
				s_x = ((j) * m) + os;
				s_y = ((i) * m) + os;
				e_x = ((j) * m) + os;
				e_y = ((i + 1) * m) - os;
				add_bound(game, (t_bvertices){s_x, s_y, e_x, e_y}, EAST);

				//bot face.
				s_x = ((j) * m) + os;
				s_y = ((i + 1) * m) - os;
				e_x = ((j + 1) * m) - os;
				e_y = ((i + 1) * m) - os;
				add_bound(game, (t_bvertices){s_x, s_y, e_x, e_y}, NORTH);

				//right face
				s_x = ((j + 1) * m) - os;
				s_y = ((i + 1) * m) - os;
				e_x = ((j + 1) * m) - os;
				e_y = ((i) * m) + os;
				add_bound(game, (t_bvertices){s_x, s_y, e_x, e_y}, WEST);
			}			
			j++;
		}	
		i++;	
	}
	return (0);
}
