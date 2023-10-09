/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lxu <lxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:13:50 by lxu               #+#    #+#             */
/*   Updated: 2023/10/07 17:46:55 by lxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	is_valid_line_colour(char *line)
{
	char	*trimmed_line;

	if (!line)
	{
		return (0);
	}
	trimmed_line = ft_strtrim(line, " ");
	if (!trimmed_line)
	{
		return (0);
	}
	if (ft_strncmp(trimmed_line, "F ", 2) != 0 && \
		ft_strncmp(trimmed_line, "C ", 2) != 0)
	{
		free(trimmed_line);
		return (0);
	}
	free(trimmed_line);
	return (1);
}

t_char_and_rgb	arr_to_colour_data(char type, char **arr)
{
	t_char_and_rgb	res;

	if (arr_len(arr) != 3)
	{
		res.c = '\0';
		return (res);
	}
	res.r = ft_atoi(arr[0]);
	res.g = ft_atoi(arr[1]);
	res.b = ft_atoi(arr[2]);
	if (res.r < 0 || res.r > 255 || \
		res.g < 0 || res.g > 255 || res.b < 0 || res.b > 255)
	{
		res.c = '\0';
		return (res);
	}
	res.c = type;
	return (res);
}

t_char_and_rgb	line_to_colour_data(char *line)
{
	t_char_and_rgb	res;
	char			type;
	char			*trimmed_line;
	char			**split_strs;

	res.c = '\0';
	trimmed_line = ft_strtrim(line, " ");
	if (!trimmed_line)
		return (res);
	if (ft_strncmp(trimmed_line, "F ", 2) == 0)
		type = 'F';
	if (ft_strncmp(trimmed_line, "C ", 2) == 0)
		type = 'C';
	split_strs = ft_split(&trimmed_line[2], ',');
	free(trimmed_line);
	res = arr_to_colour_data(type, split_strs);
	free_char_array(split_strs);
	return (res);
}

int	can_poke_colour_data(t_parsed_data *data, t_char_and_rgb rgb)
{
	if (rgb.c == 'F' && data->floor_r == -1 && \
		data->floor_g == -1 && data->floor_b == -1)
	{
		return (1);
	}
	if (rgb.c == 'C' && data->ceiling_r == -1 && \
		data->ceiling_g == -1 && data->ceiling_b == -1)
	{
		return (1);
	}
	return (0);
}

void	poke_colour_data(t_parsed_data *data, t_char_and_rgb rgb)
{
	if (rgb.c == 'F')
	{
		data->floor_r = rgb.r;
		data->floor_g = rgb.g;
		data->floor_b = rgb.b;
	}
	if (rgb.c == 'C')
	{
		data->ceiling_r = rgb.r;
		data->ceiling_g = rgb.g;
		data->ceiling_b = rgb.b;
	}
}
