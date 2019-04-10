/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_a.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 15:50:11 by mbartole          #+#    #+#             */
/*   Updated: 2019/04/10 02:51:57 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

int	get_rot(t_list *st, int to_push, int i, int len_b, char *fl)
{
	int		rot;
	int		first;
	int		last;
	int		ret;
	int		len_a;

	len_a = ft_lstlen(st);
	first = ICONT(st);
	last = last_elem(st);
	rot = 0;
	while (!can_insert(to_push, first, last))
	{
		rot++;
		last = first;
		st = st->next;
		first = ICONT(st);
	}
	ret = MAX(rot, i);
	*fl = 11;
	if (MAX(len_b - i, len_a - rot) < ret && (*fl = 22))
		ret = MAX(len_b - i, len_a - rot);
	if (i + ABS(rot - len_a) < ret && (*fl = 12))
		ret = i + ABS(rot - len_a);
	if (rot + ABS(i - len_b) < ret && (*fl = 21))
		ret = rot + ABS(i - len_b);
	return (ret);
}

t_list	*perform_rot(t_list **a, t_list **b, int to_push, char fl)
{
	t_list	*comm;
	t_list	*new;

	comm = NULL;
	if (fl / 10 == fl % 10)
	{
		while (ICONT(*b) != to_push && !can_insert(to_push, ICONT(*a),
					last_elem(*a)))
			add_and_do(&comm, a, b, fl / 10 == 1 ? "rr" : "rrr");
		while (ICONT(*b) != to_push)
			add_and_do(&comm, a, b, fl / 10 == 1 ? "rb" : "rrb");
		while (!can_insert(to_push, ICONT(*a), last_elem(*a)))
			add_and_do(&comm, a, b, fl / 10 == 1 ? "ra" : "rra");
	}
	else
	{
		while (ICONT(*b) != to_push)
			add_and_do(&comm, a, b, fl / 10 == 1 ? "rb" : "rrb");
		while (!can_insert(to_push, ICONT(*a), last_elem(*a)))
			add_and_do(&comm, a, b, fl % 10 == 1 ? "ra" : "rra");
	}
	return (comm);
}

static t_list	*adjust_stacks(t_list **a, t_list **b)
{
	t_list	*cp;
	int		i;
	int		rot;
	int		min_rot;
	int		to_push;
	int		len_b;
	char	fl;
	char	min_fl;

	len_b = ft_lstlen(*b);
	min_rot = MAX(len_b, ft_lstlen(*a));
	to_push = 0;
	min_fl = 0;
	cp = *b;
	i = 0;
	while (cp)
	{
		if (i < min_rot || len_b - i < min_rot)
		{
			rot = get_rot(*a, ICONT(cp), i, len_b, &fl);
			if (rot < min_rot)
			{
				min_rot = rot;
				to_push = ICONT(cp);
				min_fl = fl;
			}
		}
		cp = cp->next;
		i++;
	}
	return (perform_rot(a, b, to_push, min_fl));
}

/*
** push elements back to sorted A from chaos B
** [length_of_B / 2] times (plus bonuses)
*/

t_list	*back_to_a(t_list **a, t_list **b)
{
	t_list	*comm;
	int		count;

	count = ft_lstlen(*b) / 2;
	comm = NULL;
	while (count--)
	{
		add_comm(&comm, adjust_stacks(a, b));
		add_and_do(&comm, a, b, "pa");
	}
	return (comm);
}
