/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vput.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 18:33:58 by mbartole          #+#    #+#             */
/*   Updated: 2019/01/26 13:32:56 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

void	ft_vprint(t_vector b)
{
	ft_putstr("[");
	ft_putstr(b.cont);
	ft_putstr("]");
	ft_putstr(" [offset = ");
	ft_putnbr(b.offset);
	ft_putstr("]");
	ft_putstr(" [len = ");
	ft_putnbr(b.len);
	ft_putstr("]");
	ft_putstr(" [buf_size = ");
	ft_putnbr(b.v_size);
	ft_putstr("]\n");
}
