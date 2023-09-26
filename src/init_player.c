/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 15:16:09 by ivanderw          #+#    #+#             */
/*   Updated: 2023/09/26 15:30:41 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init_player.h"

//game->player.rot = 0;

int is_player_char(char c)
{
	if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
		return (1);
	return (0);
}

void	c3d_set_player_rot(t_game *game, char p_dir)
{
	if (p_dir == 'E')
		game->player.rot = 0;
	else if (p_dir == 'N')
		game->player.rot = 270;
	else if (p_dir == 'W')
		game->player.rot = 180;
	else if (p_dir == 'S')
		game->player.rot = 90;
	else
	{
		printf("c3d_internal: c3d_set_player_rot fail\n");
		game->player.rot = 0;
	}
}


int	c3d_set_player_pos(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->raw[i])
	{
		j = 0;
		while (game->raw[i][j])
		{
			if (is_player_char(game->raw[i][j]))
			{
				game->player.pos.y = (i * 64) + 32;
				game->player.pos.x = (j * 64) + 32;
				c3d_set_player_rot(game, game->raw[i][j]);	
			}	
			j++;
		}
		i++;
	}
	return (0);
}

