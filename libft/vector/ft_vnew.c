/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 13:27:28 by mbartole          #+#    #+#             */
/*   Updated: 2019/01/26 13:32:43 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vector	*ft_vnew(t_vector **v, size_t v_size)
{
	if (!(*v = (t_vector *)malloc(sizeof(t_vector))))
		return (NULL);
	if (!((*v)->cont = ft_memalloc(v_size)))
	{
		free(*v);
		*v = NULL;
		return (NULL);
	}
	(*v)->v_size = v_size;
	(*v)->len = 0;
	(*v)->offset = 0;
	return (*v);
}
