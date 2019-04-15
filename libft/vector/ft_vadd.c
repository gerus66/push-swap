/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vadd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 03:31:02 by mbartole          #+#    #+#             */
/*   Updated: 2019/01/26 13:31:01 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vector	*ft_vadd(t_vector *v, void *cont, size_t c_size)
{
	void	*tmp;

	if (c_size > (v->v_size - v->len - 1))
	{
		v->v_size *= 2;
		tmp = v->cont;
		if (!(v->cont = ft_memalloc(v->v_size)))
		{
			free(tmp);
			return (NULL);
		}
		ft_memcpy(v->cont, tmp, v->len);
		free(tmp);
	}
	ft_memcpy(v->cont + v->len, cont, c_size);
	v->len = v->len + c_size;
	return (v);
}
