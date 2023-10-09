/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 10:58:52 by ivanderw          #+#    #+#             */
/*   Updated: 2023/10/09 20:26:18 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEN_UTILS_H
# define GEN_UTILS_H

# include "libraries.h"
# include "parse.h"

void	delete_bounds_data(t_game *game);
void	free_array(char **my_array);
void	ft_start_exit(char *error_msg, t_game *m_game);
int		on_x_press(t_game *game);
void	free_bounds(t_bound *head);

#endif
