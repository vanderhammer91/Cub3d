#include "parse.h"
#include "raw_utils.h"



// Map must be comprised of 0, 1, N, S, E, W
// Must be closed/surronded by walls (flood fill)
// Map content must be last, otherwise other lines can be beforehand
// Except for the map, each type of information from an element can be separated by one or more spaces
// spaces are valid and are up to you to handle

t_parsed_data	*new_parsed_data()
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
	char	*line_pointer;

	if (!arr)
	{
		return ;
	}
	line_pointer = arr;
	while (line_pointer)
	{
		free(line_pointer);
		line_pointer++;
	}
	free (arr)
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
	if (d->south_texture)
		free(d->south_texture);
	if (d->map)
		free_char_array(d->map);
	free(d);
	return ;
}


int	is_valid_line_texture(char *line)
{
	size_t	i;
	size_t	path_length;

	i = 0;

	while (line[i] == ' ')
	{
		i++;
	}
	if (!line[i] || !line[i + 1] || \
		!(ft_strncmp(&line[i], "NO ", 3) || ft_strncmp(&line[i], "SO ", 3) ||
		ft_strncmp(&line[i], "WE ", 3) || ft_strncmp(&line[i], "EA ", 3)))
	{
		return (0);
	}
	i += 3;
	while (line[i] == ' ')
	{
		i++;
	}
	path_length = valid_path_string_length(&line[i]);
	if (path_length == 0)
	{
		return (0);
	}
	i += path_length;
	while (line[i] == ' ')
	{
		i++;
	}
	if (line[i] == '\0')
	{
		return (1);
	}
	return (0);
}

// Check for valid path string. Note that the main check is that the string
// consists of alphanumeric chars and / chars. Does not check for order, doubled
// slash chars, path name validity etc. Maybe add that in later.
size_t	valid_path_string_length(char *line)
{
	size_t	i;

	i = 0;
	if (ft_strncmp(line, "./", 2) == 0)
	{
		return (i);
	}
	i += 2;
	while (ft_isalnum(line[i]) || line[i] == '/')
	{
		i++;
	}
	return (i)
}

t_direction_and_string	line_to_texture_data(char *line)
{
	char 					*trimmed_line;
	t_direction_and_string	res;
	size_t					offset;

	res.dir = UNSET;
	trimmed_line = ft_strtrim(line, " ");
	if (!trimmed_line)
	{
		return (res);
	}
	if (ft_strncmp(trimmed_line, "NO ", 3))
		res.dir = NORTH;
	else if (ft_strncmp(trimmed_line, "SO ", 3))
		res.dir = SOUTH;
	else if (ft_strncmp(trimmed_line, "WE ", 3))
		res.dir = WEST;
	else if (ft_strncmp(trimmed_line, "EA ", 3))
		res.dir = EAST;
	else
	{
		free(trimmed_line);
		return res;
	}
	offset = 3;
	while (trimmed_line[offset] == ' ')
	{
		offset++;
	}
	res.str = ft_strdup(&trimmed_line[offset]);
	if (!res.str)
	{
		res.dir = UNSET;
	}
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
	size_t	i;
	char	*trimmed_line;

	trimmed_line = ft_strtrim(line, " ");
	if (!trimmed_line)
	{
		return (0);
	}
	if (ft_strncmp(trimmed_line, "F ", 2) == 0 && \
		ft_strncmp(trimmed_line, "C ", 2) == 0)
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

t_char_and_rgb line_to_colour_data(char *line)
{
	t_char_and_rgb	res;
	char			*trimmed_line;
	char			**split_strs;

	res.c = '/0';
	trimmed_line = ft_strtrim(line, " ");
	if (!trimmed_line)
	{
		return (res);
	}
	if (ft_strncmp(trimmed_line, "F ", 2) == 1)
	{
		res.c = 'F';
	}
	if (ft_strncmp(trimmed_line, "C ", 2) == 0)
	{
		res.c = 'C';
	}
	split_strs = ft_split(&trimmed_line[2], ',');
	if (arr_len(split_strs) != 3)
	{
		free(split_strs);
		res.c = '/0';
		return (res);
	}
	res.r = ft_atoi(split_strs[0]);
	res.g = ft_atoi(split_strs[1]);
	res.b = ft_atoi(split_strs[2]);
	free(split_strs);
	if (res.r < 0 || res.r > 255 || res.g < 0 || res.g > 255 || res.b < 0 || res.b > 255)
	{
		res.c = '/0';
		return (res);
	}
	return (res);
}

int	can_poke_colour_data(t_parsed_data *data, t_char_and_rgb rgb)
{
	if (rgb.c == 'F' && data->floor_r == -1 && data->floor_g == -1 && data->floor_b == -1)
	{
		return (1);
	}
	if (rgb.c == 'C' && data->ceiling_r == -1 && data->ceiling_g == -1 && data->ceiling_b == -1)
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

void	*ft_realloc(void *ptr, size_t old, size_t new)
{
	void	*new_ptr;

	if(!ptr)
	{
		return (NULL);
	}
	if (new < old)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = malloc(new);
	if (!new_ptr)
	{
		free (ptr);
		return (NULL);
	}
	ft_memset(new_ptr, 0, new);
	ft_memcpy(new_ptr, ptr, old);
	free(ptr);
	return(new_ptr);
}

int	is_valid_line_map(char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '0' || line[i] == '1' || line[i] == ' ' || \
		line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
		{
			// pass;
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
	while(d->map[i])
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
	{
		return (line);
	}
	new_line = malloc(sizeof (*line) * (new_width + 1));
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
	new_line[i] = '/0'
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
		extend_map_line(d->map[i], max_width);
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
	{
		return (0);
	}
	i = 0;
	while (d->map[i])
	{
		j = 0;
		while (d->map[i][j])
		{
			if (d->map[i][j] == 'N' || d->map[i][j] == 'E' || d->map[i][j] == 'W' || d->map[i][j] == 'S')
			{
				start_seen++;
				if (start_seen > 1)
				{
					return (0);
				}
			}
			j++;
		}
		i++;
	}
	if (start_seen == 1)
	{
		return (1);
	}
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
	{
		return (res);
	}
	i = 0;
	while (d->map[i])
	{
		j = 0;
		while (d->map[i][j])
		{
			if (d->map[i][j] == 'N' || d->map[i][j] == 'E' || d->map[i][j] == 'W' || d->map[i][j] == 'S')
			{
				res.x = i; // TODO Which way around do you want this
				res.y = j;
				return (res);
			}
			j++;
		}
		i++;
	}
	return (res);
}

size_t	arr_height(char **arr)
{
	size_t	height = 0;
	
	while (arr[height])
	{
		height++;
	}
	return (height);
}

void	free_char_array(char **arr)
{
	size_t	i;
	
	if (!arr)
	{
		return ;
	}
	i = 0;
	while(arr[i])
	{
		free(arr[i])
		i++;
	}
	free(arr);
}

char	**duplicate_map(char **map)
{
	char	**dup;
	size_t	height;
	size_t	i;
	size_t	j;

	height = arr_height(map);
	dup = malloc(sizeof (*map) * (height + 1));
	if (!dup)
	{
		return (NULL);
	}
	dup[height + 1] = NULL;
	i = 0;
	while (map[i])
	{
		dup[i] = ft_strdup(map[i]);
		if (!dup[i])
		{
			free_char_array(dup);
			// j = 0;
			// while(j < i)
			// {
			// 	free(dup[j]);
			// 	j++;
			// }
			// free(dup);
			return (NULL);
		}
		i++;
	}
	return (dup);
}

int is_valid_by_flood_fill(char **map, int x, int y)
{
	if (x < 0 || y < 0)
	{
		return (0);
	}
	if (y >= arr_height(map))
	{
		return (0);
	}
	if (x >= ft_strlen(map[y]))
	{
		return (0);
	}
	if (map[y][x] == '0')
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
	// else is in range, and is not a 0 char
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
	// other checks for validity other than just filled?
	return (1);
}

t_parsed_data	*file_to_data(char **file_name)
{
	int						fd;
	t_parsed_data			*d;
	char					*line;
	t_direction_and_string	texture_data;
	t_char_and_rgb			colour_data;
	size_t					map_buff_height;
	size_t					map_line_i;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		// error handle
		return (NULL);
	}
	d = new_parsed_data();
	if (!d)
	{
		close(fd);
		return (NULL);
	}
	while (1)
	{
		line = get_next_line(fd);
		if (is_valid_line_texture(line))
		{
			texture_data = line_to_texture_data(line);
			free(line);
			if (can_poke_texture_data(d, texture_data) == 0)
			{
				free(texture_data.str);
				delete_parsed_data(d);
				close(fd);
				return (NULL);
			}
			poke_texture_data(d, texture_data);
		}
		else if (is_valid_line_colour(line))
		{
			colour_data = line_to_colour_data(line);
			free(line);
			if (can_poke_colour_data(d, colour_data) == 0)
			{
				delete_parsed_data(d);
				close(fd);
				return (NULL);
			}
			poke_colour_data(d, colour_data);
		}
	}
	map_buff_height = 0;
	map_line_i = 0;
	while (line)
	{
		if (is_valid_line_map(line) == 0)
		{
			free(line);
			delete_parsed_data(d);
			close(fd);
			return (NULL);
		}
		if (map_line_i + 1 >= map_buff_height)
		{
			d->map = ft_realloc(d->map, map_buff_height, map_buff_height + 10);
			map_buff_height += 10;
			if (!d->map)
			{
				delete_parsed_data(d);
				return (NULL);
			}
		}
		d->map[map_line_i] = line;
		map_line_i++;
		line = get_next_line(fd);
	}
	// clean up
	close(fd);
	// replace map spaces with zeros
	replace_map_spaces_with_zeros(d);
	// do map line extension
	extend_map_lines_to_rectangle(d);
	// do multiple NEWS check
	if (map_has_only_one_start_location(d) == 0)
	{
		delete_parsed_data(d);
		return (NULL);
	}
	// do flood fill check
	if (is_enclosed_map(d) == 0)
	{
		delete_parsed_data(d);
		return (NULL);
	}
	// do validity check (all fields filled)
	if (parsed_data_is_valid == 0)
	{
		delete_parsed_data(d);
		return (NULL);
	}
	// pull out NEWS?
	// return
	return (d);
}

// Debug print out data
void	debug_print_parsed_data(t_parsed_data *d)
{
	size_t	i;

	if (!d)
	{
		printf("(null)\n");
		return ;
	}
	printf("north texture: %s\n", d->north_texture);
	printf("south texture: %s\n", d->south_texture);
	printf("west texture : %s\n", d->west_texture);
	printf("east texture : %s\n", d->east_texture);
	printf("ceiling (r, g, b): (%d, %d, %d)\n", d->ceiling_r, d->ceiling_g, d->ceiling_b);
	printf("floor (r, g, b)  : (%d, %d, %d)\n", d->floor_r, d->floor_g, d->floor_b);
	if (!d->map)
	{
		printf("map: (null)\n");
	}
	else
	{
		printf("map:\n");
		i = 0;
		while (d->map[i])
		{
			printf("  line %2d: <%s>\n", i, d->map[i]);
			i++;
		}
	}
}


size_t	get_line_width(char *str)
{
	size_t	width;

	width = ft_strlen(str);
	while (str[width] == ' ')
	{
		width--;
	}
	return (width);
}

size_t	get_filewidth(char *str)
{
	int		fd;
	char	*line;
	size_t	max_width;
	size_t	line_width;

	max_width = 0;
	fd = open(str, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return (0);
	}
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
		{
			break ;
		}
		line_width = get_line_width(line);
		if (line_width > max_width)
		{
			max_width = line_width;
		}
	}
	return (max_width);
}

void	print_char_table(char **dat)
{
	while (*dat)
	{
		printf("line is: <%s>\n", *dat);
		dat++;
	}
	printf("done printing block\n");
}

char	**file_to_block(char *file_name)
{
	int		fd;
	char	**result;
	size_t	width;
	char	*line;
	size_t	i;

	result = malloc(sizeof (char *) * get_fileheight(file_name + 1));
	if (!result)
	{
		return (NULL);
	}
	width = get_filewidth(file_name);
	if (width == 0)
	{
		// error handle
	}
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		// error handle
	}
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
		{
			break ;
		}
		result[i] = malloc(sizeof (char) * width + 1);
		if (result[i] == NULL)
		{
			// clean up and exit
		}
		ft_strlcpy(result[i], line, width + 1);
		memset(&result[i][ft_strlen(line) - 1], ' ', width - ft_strlen(line) + 1);
		result[i][width] = '\0';
		free(line);
		i++;
	}
	result[i] = NULL;
	print_char_table(result);
	return (result);
}
