/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 13:27:28 by mbartole          #+#    #+#             */
/*   Updated: 2019/01/26 16:08:58 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*tmp;

	if (!(tmp = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	tmp->next = NULL;
	if (content == NULL)
	{
		tmp->l_size = 0;
		tmp->cont = NULL;
		return (tmp);
	}
	tmp->l_size = content_size;
	if (!(tmp->cont = ft_memalloc(content_size)))
	{
		free(tmp);
		return (NULL);
	}
	ft_memcpy(tmp->cont, content, content_size);
	return (tmp);
}
