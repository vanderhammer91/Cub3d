/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lxu <lxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:13:50 by lxu               #+#    #+#             */
/*   Updated: 2023/10/09 11:20:45 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

// return 1 if successful (or error). 0 if unsuccessful
int	try_parse_as_texture_line(t_parsed_data *d, char *line, int *err)
{
	t_type_and_string	texture_data;

	*err = 0;
	if (is_valid_line_texture(line) == 0)
	{
		return (0);
	}
	texture_data = line_to_texture_data(line);
	if (can_poke_texture_data(d, texture_data) == 0)
	{
		free(texture_data.str);
		*err = 1;
		return (1);
	}
	poke_texture_data(d, texture_data);
	return (1);
}

int	try_parse_as_colour_line(t_parsed_data *d, char *line, int *err)
{
	t_char_and_rgb	colour_data;

	*err = 0;
	if (is_valid_line_colour(line) == 0)
	{
		return (0);
	}
	colour_data = line_to_colour_data(line);
	if (can_poke_colour_data(d, colour_data) == 0)
	{
		*err = 1;
		return (1);
	}
	poke_colour_data(d, colour_data);
	return (1);
}

int	try_parse_as_empty_line(t_parsed_data *d, char *line, int *err)
{
	(void)d;
	*err = 0;
	if (line && line[0] == '\0')
	{
		return (1);
	}
	return (0);
}

int	parse_fd_to_map(t_parsed_data *d, int fd, char *line)
{
	size_t	buff_height;
	size_t	i;

	buff_height = 0;
	i = 0;
	while (line)
	{
		if (is_valid_line_map(line) == 1)
		{
			if (i + 1 >= buff_height)
			{
				d->map = ft_realloc(d->map, buff_height, buff_height + 10);
				buff_height += 10;
				if (!d->map)
					return (free(line), -1);
			}
			d->map[i] = line;
			i++;
		}
		else
			return (free(line), -1);
		line = get_next_line_cleaned(fd);
	}
	return (0);
}

t_parsed_data	*file_to_data(char *file_name)
{
	int						fd;
	t_parsed_data			*d;
	char					*line;
	int						err;

	if (initial_checks(file_name, &fd, &d) == -1)
		return (NULL);
	while (1)
	{
		line = get_next_line_cleaned(fd);
		if (try_parse_as_texture_line(d, line, &err) || \
			try_parse_as_colour_line(d, line, &err))
		{
			free(line);
			if (err)
				return (delete_parsed_data(d), close(fd), NULL);
		}
		else
			break ;
	}
	if (parse_fd_to_map(d, fd, line) == -1)
		return (delete_parsed_data(d), close(fd), NULL);
	close(fd);
	d = final_checks(d);
	return (d);
}
