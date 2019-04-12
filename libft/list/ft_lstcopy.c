/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcopy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 16:10:11 by mbartole          #+#    #+#             */
/*   Updated: 2019/04/12 16:14:50 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

t_list	*ft_lstcopy(t_list *lst)
{
	t_list	*new;
	t_list	*one;

	new = NULL;
	while (lst)
	{
		if (!(one = ft_lstnew(lst->cont, lst->l_size)))
			return (NULL);
		ft_lstadd_back(&new, one);
		lst = lst->next;
	}
	return (new);
}
