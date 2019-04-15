/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_conv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 12:50:27 by ahugh             #+#    #+#             */
/*   Updated: 2019/01/17 15:29:11 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

static double	dot_mv(double d, ssize_t pow)
{
	if (pow)
	{
		if (pow < 0)
			while (pow++)
				d *= 10;
		else
			while (pow--)
				d /= 10;
	}
	return (d);
}

static void		add_exp_form(char **res, ssize_t pow, char up)
{
	char		*s_pow;
	char		*tmp;

	tmp = 0;
	if ((s_pow = di_conv(pow, 2, (pow < 0 ? '-' : '+'))))
	{
		if ((tmp = ft_strjoin((up == 'E' ? "E" : "e"), s_pow)))
		{
			free(s_pow);
			s_pow = tmp;
			if ((tmp = ft_strjoin(*res, s_pow)))
			{
				free(*res);
				*res = tmp;
			}
			else
				free(*res);
		}
		free(s_pow);
	}
}

static char		*round_dec(t_print *p, ssize_t pow)
{
	char		*res;
	short		len;

	len = p->flag[2] == ' ' || p->flag[2] == '-' || p->flag[2] == '+' ? 2 : 1;
	len += p->flag[0] == '#' ? 1 : 0;
	if ((res = malloc(len + 1)))
	{
		*(double*)p->arg = dot_mv(*(double*)p->arg, pow);
		res[len--] = 0;
		if (p->flag[0] == '#')
			res[len--] = '.';
		res[len] = ((*(double*)p->arg - (char)*(double*)p->arg) > 0.5 ? \
		*(double*)p->arg + 1 : *(double*)p->arg) + 48;
		if (res[len] > '9' && ++pow)
			res[len] = '1';
		if (p->flag[2] == 32 || p->flag[2] == 43 || p->flag[2] == 45)
			res[0] = p->flag[2];
		add_exp_form(&res, pow, p->conv);
	}
	return (res);
}

char			*ee(t_print *p)
{
	ssize_t		pow;
	char		*res;
	char		*sig;
	uintmax_t	*s_bits;
	int			prc;

	if ((res = abnormal(p)))
		return (res);
	prc = p->prec == -1 ? 6 : p->prec;
	s_bits = (uintmax_t*)(double*)p->arg;
	p->flag[2] = (*s_bits >> 63 ? '-' : p->flag[2]);
	*(double*)p->arg *= (*s_bits >> 63 ? -1 : 1);
	pow = get_pow_exp(*(double*)p->arg);
	if (!(sig = get_sig(*(double*)p->arg, prc)))
		return (sig);
	p->arg += round_sig(&sig, prc, '4');
	free(sig);
	if (pow >= 0 && prc == 0)
		return (round_dec(p, pow));
	*(double*)p->arg = dot_mv(*(double*)p->arg, pow);
	res = ff(p);
	add_exp_form(&res, pow, p->conv);
	return (res);
}
