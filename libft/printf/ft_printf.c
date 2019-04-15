/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 15:25:23 by mbartole          #+#    #+#             */
/*   Updated: 2019/01/17 12:35:54 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "clrs.h"

#define RESET_COLOR "\033[00m"

static char		*manage_colors(char *cp)
{
	char	*col;
	int		i;

	if (!(EOC(cp) || GR(cp) || R(cp) || GN(cp) || Y(cp) || B(cp) || M(cp) ||
			C(cp) || W(cp)) || !(col = (char *)malloc(5)))
		return (NULL);
	i = -1;
	while (++i < 5)
		col[i] = RESET_COLOR[i];
	if (EOC(cp))
		return (col);
	else
	{
		col[2] = (cp[1] == 'b') ? '4' : '3';
		i = -1;
		while (++i < 8)
			if (g_clrs[i][0] == cp[2] && g_clrs[i][1] == cp[3] &&
					(col[3] = i + 48))
				return (col);
		free(col);
		return (NULL);
	}
}

static int		parse_color(char *st)
{
	char	*cp;
	char	*col;
	int		i;
	int		count;

	count = 0;
	cp = st;
	while (*cp)
	{
		if (*cp == '{' && *(cp + 4) == '}' && (col = manage_colors(cp)))
		{
			i = -1;
			while (++i < 5)
				cp[i] = col[i];
			free(col);
			count++;
		}
		cp++;
	}
	return (count);
}

/*
** clean all vectors and va_lists and return given result
*/

static int		clean_all(t_vector *o, t_vector *v, va_list cur_a, va_list f_a)
{
	int		res;

	va_end(cur_a);
	va_end(f_a);
	if (o && o->cont)
	{
		res = parse_color((char *)(o->cont));
		write(1, (char *)(o->cont), o->offset);
	}
	res = (!v || !o || v->offset == -1) ? -1 : o->offset - (res * 5);
	if (v && v->cont)
		free(v->cont);
	if (o && o->cont)
		free(o->cont);
	free(v);
	free(o);
	return (res);
}

/*
** parse input string into two vectors
** "out" - output string for printing, it filled step by step
** ------> cont - output string
** ------> offset - size of string to output
** "com" - command string with instructions, it renew on every step
** then print it all
** and return number of printed symbols or -1
*/

static int		parse_f(char const *f, va_list c_a, va_list f_a)
{
	t_vector	*com;
	t_vector	*out;

	if (!ft_vnew(&com, INIT_V))
		return (clean_all(NULL, com, c_a, f_a));
	if (!ft_vnew(&out, INIT_V))
		return (clean_all(out, com, c_a, f_a));
	while (ft_vreset(com) && *f)
	{
		while (*f && *f != '%')
			ft_vadd(out, (void *)f++, 1);
		if (!*f++ && (out->offset = out->len))
			return (clean_all(out, com, c_a, f_a));
		while ((LEN(*f) || FLS(*f) || SPR(*f) || SPEC(*f) || DG_0(*f)) &&
				!(*f == '$' && !(DG_0(*(f - 1)))))
			ft_vadd(com, (void *)f++, 1);
		if (*f && !p_it(out, com, c_it((char *)com->cont, *f++, c_a, f_a)))
			return (clean_all(out, com, c_a, f_a));
		out->offset = out->len;
		if (!*f)
			return (clean_all(out, com, c_a, f_a));
	}
	return (clean_all(out, com, c_a, f_a));
}

/*
** just initialise va_list
*/

int				ft_printf(char const *f, ...)
{
	va_list	current_argument;
	va_list	first_argument;

	if (!f)
		return (-1);
	va_start(first_argument, f);
	va_copy(current_argument, first_argument);
	return (parse_f(f, current_argument, first_argument));
}
