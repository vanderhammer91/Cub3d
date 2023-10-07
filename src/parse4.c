/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lxu <lxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:13:50 by lxu               #+#    #+#             */
/*   Updated: 2023/10/07 17:43:04 by lxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	can_poke_texture_data(t_parsed_data *data, t_direction_and_string pair)
{
	if (pair.dir == NORTH && data->north_texture != NULL)
	{
		return (0);
	}
	if (pair.dir == SOUTH && data->south_texture != NULL)
	{
		return (0);
	}
	if (pair.dir == EAST && data->east_texture != NULL)
	{
		return (0);
	}
	if (pair.dir == WEST && data->west_texture != NULL)
	{
		return (0);
	}
	return (1);
}

void	poke_texture_data(t_parsed_data *data, t_direction_and_string pair)
{
	if (!data)
	{
		return ;
	}
	if (pair.dir == NORTH)
	{
		data->north_texture = pair.str;
	}
	if (pair.dir == SOUTH)
	{
		data->south_texture = pair.str;
	}
	if (pair.dir == EAST)
	{
		data->east_texture = pair.str;
	}
	if (pair.dir == WEST)
	{
		data->west_texture = pair.str;
	}
}
