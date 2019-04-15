/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comm_it.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 01:20:07 by mbartole          #+#    #+#             */
/*   Updated: 2019/01/16 01:42:39 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

/*
** array of flags: [#, -/0, +/' ']
*/

static void		handle_flags(char **comm, t_print *prnt)
{
	if (**comm == '#')
		prnt->flag[0] = *(*comm)++;
	if (**comm == '-')
		prnt->flag[1] = *(*comm)++;
	if (**comm == '0')
	{
		if (prnt->flag[1] != '-')
			prnt->flag[1] = '0';
		(*comm)++;
	}
	if (**comm == '+')
		prnt->flag[2] = *(*comm)++;
	if (**comm == ' ')
	{
		if (prnt->flag[2] != '+')
			prnt->flag[2] = ' ';
		(*comm)++;
	}
}

/*
** symbols of len_modificators:
** hh = 'g'
** h  = 'h'
** l  = 'l'
** ll, j, z = 'm'
** L  = 'n'
*/

static void		handle_len_mod(char **comm, t_print *prnt)
{
	**comm = (**comm == 'L' && CONV_D(prnt->conv) ? 'n' : **comm);
	**comm = ((**comm == 'j' || **comm == 'z') ? 'm' : **comm);
	if ((prnt->len_mod - **comm) <= 0)
	{
		prnt->len_mod = **comm;
		(*comm)++;
		if (**comm == prnt->len_mod && **comm == 'h')
			prnt->len_mod--;
		else if (**comm == prnt->len_mod && **comm == 'l')
			prnt->len_mod++;
		else
			(*comm)--;
	}
	(*comm)++;
}

/*
** take argument by *:
** if there is '$' take it by argument's number,
** else take it by common order
*/

static void		handle_asterisk(char **comm, int *i, va_list cur_a, va_list f_a)
{
	va_list	tmp_a;
	char	*cp;

	(*comm)++;
	cp = *comm;
	while (DG_0(*cp))
		cp++;
	if (*cp == '$')
	{
		handle_num(comm, tmp_a, f_a);
		*i = (int)va_arg(tmp_a, void*);
		va_end(tmp_a);
	}
	else
		*i = (int)va_arg(cur_a, void*);
}

/*
** set precision from argument (by '*') or from number
*/

static void		handle_prec(char **comm, t_print *p, va_list cur_a, va_list f_a)
{
	(*comm)++;
	p->prec = handle_num(comm, cur_a, f_a);
	if (!p->prec && **comm == '*')
	{
		handle_asterisk(comm, &(p->prec), cur_a, f_a);
		if (p->prec < 0)
			p->prec = -1;
	}
}

/*
** parse command string to structure t_print
*/

void			parse_comm(char *comm, t_print *p, va_list cur_a, va_list f_a)
{
	int	tmp;

	p->prec = -1;
	while (*comm)
	{
		handle_flags(&comm, p);
		if (DG(*comm) && (tmp = handle_num(&comm, cur_a, f_a)))
			p->width = tmp;
		if (*comm == '*')
		{
			handle_asterisk(&comm, &(p->width), cur_a, f_a);
			if (p->width < 0)
			{
				p->width = -p->width;
				p->flag[1] = '-';
			}
		}
		if (*comm == '.')
			handle_prec(&comm, p, cur_a, f_a);
		if (LEN(*comm))
			handle_len_mod(&comm, p);
	}
}
