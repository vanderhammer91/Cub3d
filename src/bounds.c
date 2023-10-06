/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bounds.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 13:44:26 by ivanderw          #+#    #+#             */
/*   Updated: 2023/10/06 10:36:55 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
//#include "bounds.h"


void free_bounds(t_bound* head)
{
    t_bound* current = head;
    while (current != NULL) {
        t_bound* temp = current;
        current = current->next;
        free(temp);
    }
}
