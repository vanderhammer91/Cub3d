/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 10:58:52 by ivanderw          #+#    #+#             */
/*   Updated: 2023/10/06 21:27:57 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEN_UTILS_H
# define GEN_UTILS_H

# include "libraries.h"
# include "parse.h"

void	free_array(char **my_array);
void	ft_start_exit(char *error_msg, t_game *m_game);
int		on_x_press(t_game *game);

# endif
