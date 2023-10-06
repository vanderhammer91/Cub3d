/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 10:56:55 by ivanderw          #+#    #+#             */
/*   Updated: 2023/10/06 21:30:16 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gen_utils.h"

void	free_array(char **my_array)
{
	int	i;

	i = 0;
	if (!my_array)
		return ;
	while (my_array[i])
	{
		free(my_array[i]);
		i++;
	}
	free(my_array);
}

void	ft_start_exit(char *error_msg, t_game *game)
{
	if (ft_strlen(error_msg))
		printf("%s\n", error_msg);
	delete_parsed_data(game->parsed_data);
	exit(1);
}

int	on_x_press(t_game *game)
{
	ft_start_exit("", game);
	return (1);
}
