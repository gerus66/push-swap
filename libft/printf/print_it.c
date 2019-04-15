/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_it.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <ahugh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 01:15:42 by mbartole          #+#    #+#             */
/*   Updated: 2019/01/22 19:13:54 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prnt.h"

/*
** get output string from structure t_print
** (using fuctions according to given conversion)
*/

static char	*get_output(t_vector *out, t_print *p, char *filling, int *diff)
{
	int		i;
	char	*output;

	if (!p || !out)
		return (0);
	i = -1;
	while (PRNTS[++i])
		if (PRNTS[i] == p->conv && !(output = g_pr[i](p)))
		{
			free(p);
			return (0);
		}
	out->offset = out->len;
	*diff = p->width - ft_strlen(output);
	if (p->flag[1] == '0' && (p->prec == -1 || (!p->prec && C_S(p->conv))
				|| CONV_D(p->conv)))
		*filling = '0';
	else
		*filling = ' ';
	return (output);
}

/*
** just print output string
*/

static void	print_output(char *output, char conv, t_vector *out)
{
	if (conv == 'c' && !output[0])
		ft_vadd(out, "", 1);
	ft_vadd(out, output, ft_strlen(output));
}

/*
** get output string (by get_output) from structure,
** print it and print previous simple string from buffer
*/

int			p_it(t_vector *out, t_vector *comm, t_print *p)
{
	char	*o;
	char	*cp;
	char	filling;
	int		diff;

	if (!(o = get_output(out, p, &filling, &diff)))
	{
		comm->offset = -1;
		return (0);
	}
	cp = o;
	if ((o[0] == '-' || o[0] == '+' || o[0] == ' ') && p->flag[1] == '0'
			&& ((CONV_I(p->conv) && p->prec == -1) || CONV_D(p->conv)))
		ft_vadd(out, o++, 1);
	if (o[0] == '0' && (o[1] == 'x' || o[1] == 'X') && p->prec == -1 &&
			(C_U1(p->conv) || C_U2(p->conv)) && p->flag[1] == 48 && (o += 2))
		ft_vadd(out, o - 2, 2);
	diff = (p->conv == 'c' && !o[0]) ? diff - 1 : diff;
	(p->flag[1] == '-') ? print_output(o, p->conv, out) : 1;
	while (diff-- > 0)
		ft_vadd(out, &filling, 1);
	(p->flag[1] == '-') ? 1 : print_output(o, p->conv, out);
	free(cp);
	free(p);
	return (1);
}

/*
** create struct t_print from command string
*/

t_print		*c_it(char *comm, size_t c, va_list cur_a, va_list f_a)
{
	t_print *prnt;
	double	d;

	if (!(prnt = (t_print *)ft_memalloc(sizeof(t_print))))
		return (NULL);
	prnt->conv = (!(CONV_I(c) || C_U1(c) || C_U2(c) || CONV_D(c) || \
	C_S(c) || C_WS(c)) ? 'c' : c);
	if (c == 'D' || c == 'U' || c == 'O' || c == 'C' || c == 'S')
	{
		prnt->conv = c + 32;
		prnt->len_mod = 'l';
	}
	parse_comm(comm, prnt, cur_a, f_a);
	if (CONV_I(c) || C_U1(c) || C_U2(c) || C_S(c) || C_WS(c))
		prnt->arg = va_arg(cur_a, void*);
	else if (CONV_D(c))
	{
		d = (prnt->len_mod != 'n') ? va_arg(cur_a, double) \
		: va_arg(cur_a, long double);
		prnt->arg = (void *)&d;
	}
	else
		prnt->arg = (void *)c;
	return (prnt);
}
