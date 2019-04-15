/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_conv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 14:15:21 by ahugh             #+#    #+#             */
/*   Updated: 2019/01/15 17:40:39 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

static int		binary_len(uintmax_t num)
{
	int			len;
	uintmax_t	one;

	one = 1;
	if (num == 0)
		return (1);
	if (num >= 0xFFFFFFFF)
		len = sizeof(uintmax_t) * 8 - 1;
	else if (num > 0xFFFF)
		len = 31;
	else if (num > 0xFF)
		len = 15;
	else
		len = 7;
	while (!(num & (one << len)))
		--len;
	return (len + 1);
}

static char		*b_conv(uintmax_t num, int prc, char sh)
{
	int			shift;
	int			len;
	char		*res;
	uintmax_t	one;

	if (!prc && !num && sh != '#')
		return (ft_memalloc(1));
	shift = 0;
	one = 1;
	len = binary_len(num);
	len = (len < prc ? prc : len);
	if ((res = malloc(len + 1)))
	{
		res[len] = 0;
		while (len--)
			res[len] = (num & (one << shift++) ? 1 : 0) + 48;
	}
	return (res);
}

char			*bb(t_print *p)
{
	int			prc;

	prc = 0;
	if (p->flag[0] == '#')
	{
		if (p->len_mod == 'g')
			prc = sizeof(unsigned char) * 8;
		else if (p->len_mod == 'h')
			prc = sizeof(unsigned short) * 8;
		else if (p->len_mod == 'l')
			prc = sizeof(unsigned long) * 8;
		else if (p->len_mod == 'm')
			prc = sizeof(uintmax_t) * 8;
		else
			prc = sizeof(unsigned int) * 8;
	}
	prc = (prc > p->prec ? prc : p->prec);
	return (b_conv((uintmax_t)p->arg, prc, p->flag[0]));
}
