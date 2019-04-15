/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_a.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 15:50:11 by mbartole          #+#    #+#             */
/*   Updated: 2019/04/13 17:35:08 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

/*
** param[0] to_push
** param[1] i
** param[2] len_b
*/

int				get_rot(t_list *st, int *param, char *fl)
{
	int		rot;
	int		last;
	int		ret;
	int		len_a;

	len_a = ft_lstlen(st);
	last = last_elem(st);
	rot = 0;
	while (!can_insert(param[0], ICONT(st), last))
	{
		rot++;
		last = ICONT(st);
		st = st->next;
	}
	ret = MAX(rot, param[1]);
	*fl = 11;
	if (MAX(param[2] - param[1], len_a - rot) < ret && (*fl = 22))
		ret = MAX(param[2] - param[1], len_a - rot);
	if (param[1] + ABS(rot - len_a) < ret && (*fl = 12))
		ret = param[1] + ABS(rot - len_a);
	if (rot + ABS(param[1] - param[2]) < ret && (*fl = 21))
		ret = rot + ABS(param[1] - param[2]);
	return (ret);
}

void			perform_rot(t_stacks *all, int to_push, char fl)
{
	if (fl / 10 == fl % 10)
	{
		while (ICONT(all->b) != to_push && !can_insert(to_push, ICONT(all->a),
					last_elem(all->a)))
			add_and_do(all, &all->local_comm, fl / 10 == 1 ? "rr" : "rrr");
		while (ICONT(all->b) != to_push)
			add_and_do(all, &all->local_comm, fl / 10 == 1 ? "rb" : "rrb");
		while (!can_insert(to_push, ICONT(all->a), last_elem(all->a)))
			add_and_do(all, &all->local_comm, fl / 10 == 1 ? "ra" : "rra");
	}
	else
	{
		while (ICONT(all->b) != to_push)
			add_and_do(all, &all->local_comm, fl / 10 == 1 ? "rb" : "rrb");
		while (!can_insert(to_push, ICONT(all->a), last_elem(all->a)))
			add_and_do(all, &all->local_comm, fl % 10 == 1 ? "ra" : "rra");
	}
}

/*
** rot[0] rot;
** rot[1] min_rot;
** fl[0] fl;
** fl[1] min_fl;
*/

static void		adjust_stacks(t_stacks *all)
{
	t_list	*cp;
	int		rot[2];
	char	fl[2];
	int		i;
	int		to_push;

	rot[1] = MAX(all->len_b, all->len_a);
	to_push = 0;
	fl[1] = 0;
	cp = all->b;
	i = -1;
	while (cp && ++i >= 0)
	{
		if (i < rot[1] || all->len_b - i < rot[1])
		{
			rot[0] = get_rot(all->a, (int[]){ICONT(cp), i, all->len_b}, &fl[0]);
			if (rot[0] < rot[1] && (fl[1] = fl[0]))
			{
				rot[1] = rot[0];
				to_push = ICONT(cp);
			}
		}
		cp = cp->next;
	}
	perform_rot(all, to_push, fl[1]);
}

/*
** push elements back to sorted A from chaos B
** [length_of_B / 2] times (plus bonuses)
*/

void			back_to_a(t_stacks *all)
{
	int		count;

	count = all->len_b / 2;
	while (count--)
	{
		adjust_stacks(all);
		add_and_do(all, &all->local_comm, "pa");
		all->len_a++;
		all->len_b--;
	}
	ft_lstadd_back(&all->comm, all->local_comm);
	all->local_comm = NULL;
}
