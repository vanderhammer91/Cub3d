/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 10:56:55 by ivanderw          #+#    #+#             */
/*   Updated: 2023/09/26 16:40:03 by ivanderw         ###   ########.fr       */
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

int	on_x_press(void)
{
	//free_array(m_game->map);
	exit(0);
}

void	ft_start_exit(char *error_msg, t_game *m_game)
{
	
	printf("%s\n", error_msg);
	free_array(m_game->raw);	
	exit(1);
}

