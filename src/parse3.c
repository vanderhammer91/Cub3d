/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lxu <lxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:13:50 by lxu               #+#    #+#             */
/*   Updated: 2023/10/09 11:22:38 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

//TODO decide what is a valid filename? apparently can contain any byte other
// than NUL or /
// Ref:
// https://stackoverflow.com/questions/4814040/allowed-characters-in-filename
size_t	valid_path_string_length(char *line)
{
	size_t	i;

	i = 0;
	while (ft_isalnum(line[i]) || line[i] == '/' || \
		line[i] == '_' || line[i] == '.')
	{
		i++;
	}
	return (i);
}

int	line_starts_with_direction_chars(char *line)
{
	if (!line)
	{
		return (0);
	}
	if (!line[0] || !line[1])
	{
		return (0);
	}
	if (ft_strncmp(line, "NO ", 3) == 0 || \
		ft_strncmp(line, "SO ", 3) == 0 || \
		ft_strncmp(line, "WE ", 3) == 0 || \
		ft_strncmp(line, "EA ", 3) == 0)
	{
		return (1);
	}
	return (0);
}

int	is_valid_line_texture(char *line)
{
	size_t	i;
	size_t	path_length;

	if (!line)
		return (0);
	i = 0;
	while (line[i] == ' ')
		i++;
	if (line_starts_with_direction_chars(&line[i]) == 0)
		return (0);
	i += 3;
	while (line[i] == ' ')
		i++;
	path_length = valid_path_string_length(&line[i]);
	if (path_length == 0)
		return (0);
	i += path_length;
	while (line[i] == ' ')
		i++;
	if (line[i] == '\0')
		return (1);
	return (0);
}

enum e_wall_type	str_to_direction(char *str)
{
	if (ft_strncmp(str, "NO", 2) == 0)
	{
		return (NORTH);
	}
	if (ft_strncmp(str, "SO", 2) == 0)
	{
		return (SOUTH);
	}
	if (ft_strncmp(str, "WE", 2) == 0)
	{
		return (WEST);
	}
	if (ft_strncmp(str, "EA", 2) == 0)
	{
		return (EAST);
	}
	return (UNSET);
}

t_type_and_string	line_to_texture_data(char *line)
{
	char					*trimmed_line;
	t_type_and_string	res;
	size_t					offset;

	res.dir = UNSET;
	trimmed_line = ft_strtrim(line, " ");
	if (!trimmed_line)
		return (res);
	res.dir = str_to_direction(trimmed_line);
	if (res.dir == UNSET)
	{
		free(trimmed_line);
		return (res);
	}
	offset = 3;
	while (trimmed_line[offset] == ' ')
		offset++;
	res.str = ft_strdup(&trimmed_line[offset]);
	if (!res.str)
		res.dir = UNSET;
	free(trimmed_line);
	return (res);
}
