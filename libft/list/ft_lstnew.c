/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 13:27:28 by mbartole          #+#    #+#             */
/*   Updated: 2019/01/26 13:57:29 by mbartole         ###   ########.fr       */
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
		tmp->content_size = 0;
		tmp->content = NULL;
		return (tmp);
	}
	tmp->content_size = content_size;
	if (!(tmp->content = ft_memalloc(tmp->content_size)))
	{
		free(tmp);
		return (NULL);
	}
	ft_memcpy(tmp->content, content, tmp->content_size);
	return (tmp);
}
