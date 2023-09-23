/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivanderw <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 17:20:23 by ivanderw          #+#    #+#             */
/*   Updated: 2023/03/20 17:29:26 by ivanderw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
PROTOTYPE
	t_list	*ft_lstlast(t_list *lst);

PARAMETERS
	lst: The beginning of the list.

RETURN 
	Last node of the list

no external functs.

DESCRIPTION
	returns the last node of the list.
   */
#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	while (lst)
	{
		if (lst ->next)
			lst = lst->next;
		else
			return (lst);
	}
	return (NULL);
}
