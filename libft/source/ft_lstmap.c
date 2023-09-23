/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 19:10:32 by ivanderw          #+#    #+#             */
/*   Updated: 2023/03/20 20:49:38 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
PROTOTYPE
	t_list	*ft_lstmap(t_list *lst, void * (*f)(void *), void (*del)(void *));

PARAMETERS
	lst: The address of a pointer to a node.
	f: The address of the function used to iterate on
	the list.
	del: The address of the function used to delete
	the content of a node if needed.

RETURN
	The new list.
	NULL if the allocation fails.

EXTERNAL FUNCTIONS
	malloc, free

DESCRIPTION
	Iterates the list ’lst’ and applies the function
	’f’ on the content of each node. Creates a new
	list resulting of the successive applications of
	the function ’f’. The ’del’ function is used to
	delete the content of a node if needed.
*/
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*map_list;

	if (!lst || !f || !del)
		return (NULL);
	map_list = ft_lstnew(f(lst->content));
	lst = lst->next;
	while (lst)
	{
		ft_lstadd_back(&map_list, ft_lstnew(f(lst->content)));
		lst = lst->next;
	}
	return (&map_list[0]);
}
