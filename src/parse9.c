/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse9.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lxu <lxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:13:50 by lxu               #+#    #+#             */
/*   Updated: 2023/10/07 19:29:15 by lxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

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
