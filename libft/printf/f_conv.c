/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_conv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 15:26:45 by ahugh             #+#    #+#             */
/*   Updated: 2019/01/17 14:13:10 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

char			*get_sig(double d, size_t prc)
{
	char		*res;
	size_t		i;

	i = 0;
	d = d < 0 ? -d : d;
	d -= (uintmax_t)d;
	if ((res = malloc(++prc + 1)))
	{
		res[prc] = 0;
		while (prc--)
		{
			res[i++] = (char)(d * 10) + 48;
			d = (double)(d * 10) - (uintmax_t)(d * 10);
		}
	}
	return (res);
}

short			round_sig(char **sig, size_t prc, char edge)
{
	short		ar;

	ar = (*sig)[prc] > edge ? 1 : 0;
	if (ar)
	{
		while (prc)
		{
			(*sig)[prc] = (*sig)[prc - 1] + ((*sig)[prc - 1] == '9' ? -9 : 1);
			prc--;
			if ((*sig)[prc] != '9' && ar--)
				break ;
		}
	}
	while (prc)
	{
		(*sig)[prc] = (*sig)[prc - 1];
		prc--;
	}
	**sig = '.';
	return (ar);
}

char			*ff(t_print *p)
{
	char		*res;
	char		*dec;
	char		*sig;
	uintmax_t	*s_bit;
	int			prec;

	prec = (p->prec == -1) ? 6 : p->prec;
	s_bit = (uintmax_t*)((double*)(p->arg));
	if (*s_bit >> 63 && (p->flag[2] = '-'))
		*(double *)(p->arg) *= -1;
	if ((res = abnormal(p)))
		return (res);
	if (!(sig = get_sig(*(double *)(p->arg), prec)))
		return (sig);
	*(double *)(p->arg) += round_sig(&sig, prec, '4');
	if (!(dec = di_conv(*(double *)(p->arg), 1, p->flag[2])) \
	|| (prec == 0 && p->flag[0] != '#'))
	{
		free(sig);
		return (dec);
	}
	res = ft_strjoin(dec, sig);
	free(dec);
	free(sig);
	return (res);
}
