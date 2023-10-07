/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lxu <lxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:13:50 by lxu               #+#    #+#             */
/*   Updated: 2023/10/07 17:30:35 by lxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "raw_utils.h"



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

void	print_char_array(char **arr)
{
	size_t	i;

	printf("----char_array----\n");
	if (!arr)
		printf("(null)\n");
	else
	{
		i = 0;
		while (arr[i])
		{
			printf("line %ld (p: %p): <%s>\n", i, arr[i], arr[i]);
			i++;
		}
	}
	printf("----end----\n");
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

int line_starts_with_direction_chars(char *line)
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
t_direction_and_string	line_to_texture_data(char *line)
{
	char					*trimmed_line;
	t_direction_and_string	res;
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

size_t	arr_height(char **arr)
{
	size_t	height;

	height = 0;
	while (arr[height])
	{
		height++;
	}
	return (height);
}

char	**duplicate_map(char **map)
{
	char	**dup;
	size_t	height;
	size_t	i;
	char	*line;

	height = arr_height(map);
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
	if (y >= (int)arr_height(map))
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

void	debug_print_char_array(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
	{
		printf("  line %2ld: <%s>\n", i, arr[i]);
		i++;
	}
}

// Debug print out data
void	debug_print_parsed_data(t_parsed_data *d)
{
	if (!d)
	{
		printf("(null)\n");
		return ;
	}
	printf("north texture: %s\n", d->north_texture);
	printf("south texture: %s\n", d->south_texture);
	printf("west texture : %s\n", d->west_texture);
	printf("east texture : %s\n", d->east_texture);
	printf("ceiling (r, g, b): (%d, %d, %d)\n", \
		d->ceiling_r, d->ceiling_g, d->ceiling_b);
	printf("floor (r, g, b)  : (%d, %d, %d)\n", \
		d->floor_r, d->floor_g, d->floor_b);
	if (!d->map)
		printf("map: (null)\n");
	else
	{
		printf("map:\n");
		debug_print_char_array(d->map);
	}
}
