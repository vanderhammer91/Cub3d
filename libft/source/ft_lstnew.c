/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 16:24:52 by ivanderw          #+#    #+#             */
/*   Updated: 2023/03/20 16:48:20 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
PROTOTYPE
	t_list *ft_lstnew(void *content);

PARAMETERS
	content: The content to create the node with.

RETURN 
	The new node.

EXTERNAL FUNCTIONS
	malloc

DESCRIPTION
	Allocates (with (malloc(3)) and returns a new node.
	The member variable 'content' is initialized with the value
	of the parameter 'content'. The variable 'next' is initialized to
	NULL.
*/
#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*my_list;

	my_list = (t_list *)malloc(sizeof(t_list));
	if (!my_list)
		return (NULL);
	my_list->content = content;
	my_list->next = NULL;
	return (my_list);
}
