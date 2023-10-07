/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lxu <lxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:13:50 by lxu               #+#    #+#             */
/*   Updated: 2023/10/07 17:49:27 by lxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"


// Map must be comprised of 0, 1, N, S, E, W
// Must be closed/surronded by walls (flood fill)
// Map content must be last, otherwise other lines can be beforehand
// Except for the map, each type of information from an element can be separated
// by one or more spaces
// spaces are valid and are up to you to handle

t_parsed_data	*new_parsed_data(void)
{
	t_parsed_data	*data;

	data = malloc(sizeof(t_parsed_data) * 1);
	if (!data)
	{
		return (NULL);
	}
	data->north_texture = NULL;
	data->south_texture = NULL;
	data->west_texture = NULL;
	data->east_texture = NULL;
	data->floor_r = -1;
	data->floor_g = -1;
	data->floor_b = -1;
	data->ceiling_r = -1;
	data->ceiling_g = -1;
	data->ceiling_b = -1;
	data->map = NULL;
	return (data);
}

void	free_char_array(char **arr)
{
	size_t	i;

	if (!arr)
	{
		return ;
	}
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	delete_parsed_data(t_parsed_data *d)
{
	if (!d)
	{
		return ;
	}
	if (d->north_texture)
		free(d->north_texture);
	if (d->south_texture)
		free(d->south_texture);
	if (d->west_texture)
		free(d->west_texture);
	if (d->east_texture)
		free(d->east_texture);
	if (d->map)
	{
		free_char_array(d->map);
	}
	free(d);
	return ;
}

size_t	arr_len(char **arr)
{
	size_t	len;

	len = 0;
	while (arr[len])
	{
		len++;
	}
	return (len);
}

char	**ft_realloc(char **ptr, size_t old, size_t new)
{
	char	**new_ptr;
	size_t	i;

	if (new < old)
		return (free(ptr), NULL);
	new_ptr = malloc(sizeof (*ptr) * new);
	if (!new_ptr)
		return (free(ptr), NULL);
	i = 0;
	while (ptr && ptr[i] && i < new)
	{
		new_ptr[i] = ptr[i];
		i++;
	}
	while (i < new)
	{
		new_ptr[i] = NULL;
		i++;
	}
	free(ptr);
	return (new_ptr);
}
