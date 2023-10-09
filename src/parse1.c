/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lxu <lxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:13:50 by lxu               #+#    #+#             */
/*   Updated: 2023/10/07 17:36:26 by lxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	debug_print_char_array_for_parsed_data(char **arr)
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
		debug_print_char_array_for_parsed_data(d->map);
	}
}

void	debug_print_char_array(char **arr)
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
