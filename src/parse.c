/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lxu <lxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:13:50 by lxu               #+#    #+#             */
/*   Updated: 2023/10/07 17:51:02 by lxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	is_valid_line_map(char *line)
{
	size_t	i;

	if (!line)
	{
		return (0);
	}
	i = 0;
	while (line[i])
	{
		if (line[i] == '0' || line[i] == '1' || line[i] == ' ' || \
			line[i] == 'X' || line[i] == '2' || line[i] == '4' || \
		line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
		{
		}
		else
		{
			return (0);
		}
		i++;
	}
	return (1);
}

size_t	get_max_map_width(t_parsed_data *d)
{
	size_t	max_width;
	size_t	i;

	if (!d->map)
	{
		return (0);
	}
	max_width = 0;
	i = 0;
	while (d->map[i])
	{
		if (ft_strlen(d->map[i]) > max_width)
		{
			max_width = ft_strlen(d->map[i]);
		}
		i++;
	}
	return (max_width);
}

void	replace_map_spaces_with_zeros(t_parsed_data *d)
{
	size_t	i;
	size_t	j;

	if (!d->map)
	{
		return ;
	}
	i = 0;
	while (d->map[i])
	{
		j = 0;
		while (d->map[i][j])
		{
			if (d->map[i][j] == ' ')
			{
				d->map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
}

char	*extend_map_line(char *line, size_t new_width)
{
	char	*new_line;
	size_t	i;

	if (new_width <= ft_strlen(line))
		return (line);
	new_line = malloc(sizeof (*line) * (new_width + 1));
	if (!new_line)
		return (free(line), NULL);
	i = 0;
	while (line[i])
	{
		new_line[i] = line[i];
		i++;
	}
	while (i < new_width)
	{
		new_line[i] = '0';
		i++;
	}
	new_line[i] = '\0';
	free(line);
	return (new_line);
}

void	extend_map_lines_to_rectangle(t_parsed_data *d)
{
	size_t	max_width;
	size_t	i;

	if (!d->map)
	{
		return ;
	}
	max_width = get_max_map_width(d);
	i = 0;
	while (d->map[i])
	{
		d->map[i] = extend_map_line(d->map[i], max_width);
		i++;
	}
}

int	map_has_only_one_start_location(t_parsed_data *d)
{
	int		start_seen;
	size_t	i;
	size_t	j;

	start_seen = 0;
	if (!d->map)
		return (0);
	i = 0;
	while (d->map[i])
	{
		j = 0;
		while (d->map[i][j])
		{
			if (d->map[i][j] == 'N' || d->map[i][j] == 'E' || \
				d->map[i][j] == 'W' || d->map[i][j] == 'S')
				start_seen++;
			j++;
		}
		i++;
	}
	if (start_seen == 1)
		return (1);
	return (0);
}

t_coord	get_start_location(t_parsed_data *d)
{
	t_coord	res;
	size_t	i;
	size_t	j;

	res.x = -1;
	res.y = -1;
	if (!d->map)
		return (res);
	i = 0;
	while (d->map[i])
	{
		j = 0;
		while (d->map[i][j])
		{
			if (d->map[i][j] == 'N' || d->map[i][j] == 'E' || \
				d->map[i][j] == 'W' || d->map[i][j] == 'S')
			{
				return (res.x = j, res.y = i, res);
			}
			j++;
		}
		i++;
	}
	return (res);
}

char	**duplicate_map(char **map)
{
	char	**dup;
	size_t	height;
	size_t	i;
	char	*line;

	height = arr_len(map);
	dup = malloc(sizeof (*map) * (height + 1));
	if (!dup)
		return (NULL);
	dup[height] = NULL;
	i = 0;
	while (map[i])
	{
		line = ft_strdup(map[i]);
		if (!line)
			return (free_char_array(dup), NULL);
		dup[i] = line;
		if (!dup[i])
			return (free_char_array(dup), NULL);
		i++;
	}
	return (dup);
}

int is_valid_by_flood_fill(char **map, int x, int y)
{
	if (x < 0 || y < 0)
		return (0);
	if (y >= (int)arr_len(map))
		return (0);
	if (x >= (int)ft_strlen(map[y]))
		return (0);
	if (map[y][x] == '0' || map[y][x] == 'N' || map[y][x] == 'S' || \
		map[y][x] == 'W' || map[y][x] == 'E')
	{
		map[y][x] = 'x';
		if (is_valid_by_flood_fill(map, x - 1, y) == 0 || \
		is_valid_by_flood_fill(map, x + 1, y) == 0 || \
		is_valid_by_flood_fill(map, x, y - 1) == 0 || \
		is_valid_by_flood_fill(map, x, y + 1) == 0)
		{
			return (0);
		}
	}
	return (1);
}

int	is_enclosed_map(t_parsed_data *d)
{
	char	**dup;
	t_coord	start;
	int		res;

	if (!d)
	{
		return (0);
	}
	dup = duplicate_map(d->map);
	start = get_start_location(d);
	if (!dup || start.x < 0 || start.y < 0)
	{
		return (0);
	}
	res = is_valid_by_flood_fill(dup, start.x, start.y);
	free_char_array(dup);
	return (res);
}

// other checks for validity other than just filled?
int	parsed_data_is_valid(t_parsed_data *d)
{
	if (!d || \
	d->north_texture == NULL || \
	d->south_texture == NULL || \
	d->west_texture == NULL || \
	d->east_texture == NULL || \
	d->floor_r < 0 || d->floor_r > 255 || \
	d->floor_g < 0 || d->floor_g > 255 || \
	d->floor_b < 0 || d->floor_b > 255 || \
	d->ceiling_r < 0 || d->ceiling_r > 255 || \
	d->ceiling_g < 0 || d->ceiling_g > 255 || \
	d->ceiling_b < 0 || d->ceiling_b > 255 || \
	d->map == NULL)
	{
		return (0);
	}
	return (1);
}

void	remove_trailing_new_line_char(char *line)
{
	size_t	len;

	if (!line)
	{
		return ;
	}
	len = ft_strlen(line);
	if ((len >= 1) && line[len - 1] == '\n')
	{
		line[len - 1] = '\0';
	}
	return ;
}

int	is_file_name_valid(char *file_name)
{
	size_t	len;

	if (!file_name)
	{
		return (0);
	}
	len = ft_strlen(file_name);
	if (len < 4)
	{
		return (0);
	}
	if (ft_strncmp(&file_name[len - 4], ".cub", 5) != 0)
	{
		return (0);
	}
	return (1);
}

// return 1 if successful (or error). 0 if unsuccessful
int	try_parse_as_texture_line(t_parsed_data *d, char *line, int* err)
{
	t_direction_and_string	texture_data;

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

// get next line, except if it is an empty line it "skips" it and if it has a
// '\n' char on the end it removes it
char	*get_next_line_cleaned(int fd)
{
	char	*line;

	line = get_next_line(fd);
	remove_trailing_new_line_char(line);
	while (line && line[0] == '\0')
	{
		free (line);
		line = get_next_line(fd);
		remove_trailing_new_line_char(line);
	}
	return (line);
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
			// d->map[i + 1] = NULL;
			i++;
		}
		else
			return(free (line), -1);
		line = get_next_line_cleaned(fd);
	}
	return (0);
}

int	initial_checks(char *file_name, int *fd, t_parsed_data **d)
{
	if (is_file_name_valid(file_name) == 0)
		return (-1);
	*fd = open(file_name, O_RDONLY);
	if (*fd == -1)
		return (-1);
	*d = new_parsed_data();
	if (!*d)
	{
		close(*fd);
		return (-1);
	}
	return (0);
}

t_parsed_data	*final_checks(t_parsed_data *d)
{
	replace_map_spaces_with_zeros(d);
	extend_map_lines_to_rectangle(d);
	if (map_has_only_one_start_location(d) == 0)
	{
		delete_parsed_data(d);
		return (NULL);
	}
	if (is_enclosed_map(d) == 0)
	{
		delete_parsed_data(d);
		return (NULL);
	}
	if (parsed_data_is_valid(d) == 0)
	{
		delete_parsed_data(d);
		return (NULL);
	}
	return (d);
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
	err = parse_fd_to_map(d, fd, line);
	if (err == -1)
		return (delete_parsed_data(d), close(fd), NULL);
	close(fd);
	d = final_checks(d);
	return (d);
}
