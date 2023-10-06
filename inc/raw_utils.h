/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raw_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 14:20:10 by ivanderw          #+#    #+#             */
/*   Updated: 2023/10/06 12:51:33 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAW_UTILS_H
# define RAW_UTILS_H

# include "libraries.h"
# include "parse.h"

int		get_fileheight(char *str);
int		c3d_set_raw(char **argv, t_game *game);
void	c3d_print_raw(t_game *game);
int		get_mapheight(t_game *game);

#endif
