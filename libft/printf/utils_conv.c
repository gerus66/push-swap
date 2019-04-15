/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_conv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 22:49:05 by ahugh             #+#    #+#             */
/*   Updated: 2019/01/17 15:19:25 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#define SIG 0xFFFFFFFFFFFFF
#define MY_N "(null)"
#define UP_CASE(x) (x == 'F' || x == 'E' || x == 'G')

size_t			get_len_dec(size_t num, short base)
{
	size_t		len;

	len = 1;
	while (num > ((size_t)base - 1) && len++)
		num /= base;
	return (len);
}

ssize_t			get_pow_exp(double d)
{
	ssize_t		pow;

	pow = 0;
	while ((size_t)d > 10 && ++pow)
		d /= 10;
	if (d != 0)
		while ((size_t)d == 0 && --pow)
			d *= 10.0;
	return (pow);
}

char			*abnormal(t_print *p)
{
	char		*res;
	short		ln;
	uintmax_t	*bits;

	res = 0;
	bits = (uintmax_t*)((double*)(p->arg));
	ln = ((p->flag[2] == 32 || p->flag[2] == 43 || p->flag[2] == 45)
	&& !(*bits & SIG) ? 5 : 4);
	if (((*bits >> 52 & 0x7FF) == 0x7FF) && (res = malloc(ln)))
	{
		if (p->flag[1] == '0')
			p->flag[1] = '\0';
		if ((*bits & SIG))
			ft_memcpy(res, UP_CASE(p->conv) ? "NAN" : "nan", 3);
		else
		{
			res[0] = p->flag[2];
			ft_memcpy(&res[(ln == 5 ? 1 : 0)],
					UP_CASE(p->conv) ? "INF" : "inf", 3);
		}
		res[ln - 1] = 0;
	}
	return (res);
}

char			*reg_st(char *st, t_print *pr)
{
	int			len;
	int			prec;
	char		*ret;
	int			i;

	if (!st)
		st = MY_N;
	len = ft_strlen(st);
	prec = (pr->prec == -1 ? len : pr->prec);
	prec = (prec < len) ? prec : len;
	if (!(ret = ft_strnew(prec)))
		return (NULL);
	i = -1;
	while (++i < prec)
		ret[i] = st[i];
	return (ret);
}

char			*lch(wchar_t c)
{
	char		*r;

	r = 0;
	if (c >= 0x80 && c <= 0x7FF && (r = malloc(3)))
	{
		r[0] = c >> 6 | 0xC0;
		r[1] = (c & 0x3F) | 0x80;
		r[2] = 0;
	}
	else if (c >= 0x800 && c <= 0xFFFF && (r = malloc(4)))
	{
		r[0] = c >> 12 | 0xE0;
		r[1] = ((c >> 6) & 0x3F) | 0x80;
		r[2] = (c & 0x3F) | 0x80;
		r[3] = 0;
	}
	if (c >= 65536 && c <= 0x10FFFF && (r = malloc(5)))
	{
		r[0] = c >> 18 | 0xF0;
		r[1] = ((c >> 12) & 0x3F) | 0x80;
		r[2] = ((c >> 6) & 0x3F) | 0x80;
		r[3] = (c & 0x3F) | 0x80;
		r[4] = 0;
	}
	return (r);
}
