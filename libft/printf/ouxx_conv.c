/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ouxx_conv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 15:26:45 by ahugh             #+#    #+#             */
/*   Updated: 2019/01/17 15:44:05 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

static char	*ox_conv(size_t num, size_t pres, short base, t_print *p)
{
	size_t		len;
	size_t		n;
	char		*res;
	short		alfa;

	len = 1;
	alfa = (p->conv == 'X') ? 55 : 87;
	n = num;
	while (++len && n > (size_t)(base - 1))
		n /= base;
	if (++pres && p->flag[0] && base == 8 && num && (len += 1))
		pres += (len > pres ? 1 : 0);
	else if (p->flag[0] && base == 16 && num && (len += 2))
		pres += 2;
	len = (pres > len ? pres : len);
	n = num;
	if ((!num && pres == 1 && !(base == 8 && p->flag[0])) ||
			!(res = ft_memalloc(len--)))
		return (ft_memalloc(1));
	res[0] = '0';
	while (len-- && (res[len] = n % base + (n % base > 9 ? alfa : 48)) != 21)
		n /= base;
	if (p->flag[0] && base == 16 && num)
		res[1] = p->conv;
	return (res);
}

static char	*pp(t_print *p, size_t pr, short b)
{
	char	*res;
	char	*ret;

	p->conv = 'x';
	res = ox_conv((unsigned long)p->arg, pr, b, p);
	ret = ft_strjoin("0x", res);
	free(res);
	return (ret);
}

char		*oux(t_print *p)
{
	size_t	pr;
	short	b;

	pr = (p->prec == -1) ? 1 : (size_t)p->prec;
	b = (p->conv == 'u') ? 10 : 0;
	if (!b)
		b = (p->conv == 'o') ? 8 : 16;
	if (p->len_mod == 'g')
		return (ox_conv((unsigned char)p->arg, pr, b, p));
	else if (p->len_mod == 'h')
		return (ox_conv((unsigned short)p->arg, pr, b, p));
	else if (p->len_mod == 'l' || p->conv == 'p')
	{
		if (p->conv == 'p')
			return (pp(p, pr, b));
		return (ox_conv((unsigned long)p->arg, pr, b, p));
	}
	else if (p->len_mod == 'm')
		return (ox_conv((unsigned long long)p->arg, pr, b, p));
	else
		return (ox_conv((unsigned int)p->arg, pr, b, p));
}
