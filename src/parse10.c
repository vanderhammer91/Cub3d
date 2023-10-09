/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse10.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lxu <lxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:13:50 by lxu               #+#    #+#             */
/*   Updated: 2023/10/07 19:31:13 by lxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

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
