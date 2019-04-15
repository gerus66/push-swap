/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cs_conv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 15:26:45 by ahugh             #+#    #+#             */
/*   Updated: 2019/01/15 00:22:23 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

static char	*ch_conv(unsigned int ch, char len)
{
	char			*res;

	res = 0;
	if ((wchar_t)ch < 128 || (len != 'l' && (wchar_t)ch < 256))
	{
		if ((res = malloc(2)))
		{
			res[0] = (unsigned char)ch;
			res[1] = 0;
		}
	}
	else if (MB_CUR_MAX == 4)
		res = lch((wchar_t)ch);
	return (res);
}

static char	*gen_out(t_print *pr, int *len)
{
	*len = 0;
	while (((unsigned int *)pr->arg)[*len])
		(*len)++;
	*len = (pr->prec == -1 ? *len * MB_CUR_MAX : pr->prec);
	return (ft_strnew(*len));
}

static char	*lst(t_print *pr)
{
	char			*res;
	int				len;
	char			*out;
	int				i;

	if (!(out = gen_out(pr, &len)))
		return (NULL);
	i = -1;
	while (((unsigned int *)pr->arg)[++i])
	{
		if (!(res = ch_conv(((unsigned int *)pr->arg)[i], 'l')))
		{
			free(out);
			return (NULL);
		}
		if ((len -= ft_strlen(res)) >= 0)
			out = ft_strcat(out, res);
		else
		{
			free(res);
			break ;
		}
		free(res);
	}
	return (out);
}

char		*ch(t_print *pr)
{
	return (ch_conv((unsigned int)pr->arg, pr->len_mod));
}

char		*st(t_print *pr)
{
	if (pr->len_mod != 'l' || !pr->arg)
		return (reg_st(((char *)pr->arg), pr));
	else
		return (lst(pr));
}
