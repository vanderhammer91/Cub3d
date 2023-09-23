/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:59:55 by ivanderw          #+#    #+#             */
/*   Updated: 2023/03/20 19:09:52 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
PROTOTYPE
	void	ft_lstiter(t_list *lst, void (*f)(void *));

PARAMETERS
	lst: The address of a pointer to a node.
	f: The address of the function used to iterate on
	the list.

No return or external functions.

DESCRIPTION
	Iterates the list ’lst’ and applies the function
	’f’ on the content of each node.
*/
#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		(*f)(lst->content);
		lst = lst->next;
	}
}
