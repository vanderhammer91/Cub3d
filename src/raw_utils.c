/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raw_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lxu <lxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 16:42:36 by ivanderw          #+#    #+#             */
/*   Updated: 2023/09/25 18:01:34 by lxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "cub3d.h"
#include "raw_utils.h"
# include "parse.h"

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

int c3d_set_raw(char **argv, t_game *game)
{
	game->raw = file_to_block(argv[1]);
	return (0);
}

// int	c3d_set_raw(char **argv, t_game *game)
// {
// 	char	*line;
// 	int		fd;
// 	int		i;

// 	game->raw = malloc(sizeof(char *) * get_fileheight(argv[1]) + 1);
// 	fd = open(argv[1], O_RDONLY);
// 	if (fd == -1)
// 	{
// 		perror("open");
// 		return (1);
// 	}
// 	line = get_next_line(fd);
// 	i = 0;
// 	while (line != NULL)
// 	{
// 		game->raw[i] = ft_strdup(line);
// 		if (!game->raw[i])
// 			return (1);
// 		free(line);
// 		line = get_next_line(fd);
// 		i++;
// 	}
// 	game->raw[i] = NULL;
// 	close(fd);
// 	return (0);
// }

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
