/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vresize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 04:34:35 by mbartole          #+#    #+#             */
/*   Updated: 2019/01/26 13:33:21 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vector	*ft_vresize(t_vector *v)
{
	void	*tmp;

	if (v->len - v->offset < v->v_size / 4)
	{
		v->v_size /= 2;
		tmp = v->cont;
		if (!(v->cont = ft_memalloc(v->v_size)))
			return (NULL);
		ft_memcpy(v->cont, tmp + v->offset, v->len - v->offset);
		free(tmp);
		v->len = v->len - v->offset;
		v->offset = 0;
	}
	return (v);
}
