/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 10:58:52 by ivanderw          #+#    #+#             */
/*   Updated: 2023/09/22 14:56:30 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEN_UTILS_H
# define GEN_UTILS_H

# include "libraries.h"

void	free_array(char **my_array);
int		on_x_press(void);
void	ft_start_exit(char *error_msg, t_game *m_game);


# endif
