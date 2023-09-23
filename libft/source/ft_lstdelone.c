/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 17:47:26 by ivanderw          #+#    #+#             */
/*   Updated: 2023/03/22 12:42:47 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
PROTOTYPE
	void	ft_lstdelone(t_list *lst, void (*del)(void *));

PARAMETERS
	lst:	The node to free
	del:	The address of the function used to delete the content.

no return

EXTERNAL FUNCTIONS
	free

DESCRIPTION
	Takes as a parameter a node and frees the memory of the node's content
	using the function 'del' given as a parameter and free the node. The memory
	of 'next' must not be freed.
*/
#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst)
		return ;
	del(lst->content);
	free(lst);
}
