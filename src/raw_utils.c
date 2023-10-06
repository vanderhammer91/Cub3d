/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raw_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lxu <lxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 16:42:36 by ivanderw          #+#    #+#             */
/*   Updated: 2023/10/06 12:52:07 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raw_utils.h"

int	get_fileheight(char *str)
{
	char	*line;
	int		fd;
	int		i;
	
	fd = open(str, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return (1);
	}
	line = get_next_line(fd);
	i = 0;
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
		i++;
	}
	close(fd);
	return (i);
}

void c3d_print_raw(t_game *game)
{
	int	i;

	i = 0;
	while (game->raw[i])
	{
		printf("%s", game->raw[i]);
		i++;
	}
}

int	get_mapheight(t_game *game)
{
	int	i;

	i = 0;
	while (game->raw[i])
		i++;
	return (i);
}
