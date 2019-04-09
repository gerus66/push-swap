/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_a.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 15:50:11 by mbartole          #+#    #+#             */
/*   Updated: 2019/04/10 02:21:58 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

/*
** push one top element from stack A to somewhere in stack B (optimised)
*/

static void	one_last_rec(int *i, t_list **a, t_list **b, t_list **comm,
		char reverse)
{
		if (*i > 0 && can_insert_rev(ICONT((*a)->next), *b))
		{
			add_and_do(comm, a, b, "sa");
			add_and_do(comm, a, b, "pb");
			(*i)--;
			if (!reverse)
				add_and_do(comm, a, b, "rb");
		}
		if (*i > 1 && can_insert_rev(ICONT((*a)->next->next), *b))
		{
			add_and_do(comm, a, b, "ra");
			add_and_do(comm, a, b, "sa");
			add_and_do(comm, a, b, "pb");
/*			one_last_rec(i, a, b, comm, reverse);*/
			if (!reverse)
			{
				add_and_do(comm, a, b, "rb");
/*				one_last_rec(i, a, b, comm, reverse);*/
			}
			add_and_do(comm, a, b, "rra");
			(*i)--;
		}
}

t_list	*push_one_last(t_list **a, t_list **b, int *i)
{
	t_list	*comm;
	t_list	*cp;
	int		rot;
	char	reverse;
	int		len_b;

	comm = NULL;
	len_b = ft_lstlen(*b);
	cp = *b;
	rot = 0;
	while (!can_insert_rev(ICONT(*a), cp) && cp->next && ++rot)
		cp = cp->next;
	reverse = rot > len_b / 2 ? 1 : 0;
	if (reverse)
		rot = len_b - rot;
	while (--rot >= 0)
	{
		one_last_rec(i, a, b, &comm, reverse);
		add_and_do(&comm, a, b, reverse ? "rrb" : "rb");
	}
	add_and_do(&comm, a, b, "pb");
	return (comm);
}

int	get_rot(t_list *st, int to_push, int i, int len_b, char *fl)
{
	t_list 	*cp;
	int		rot;
	int		ret;
	int		len_a;

	cp = lst_copy(st);
	len_a = ft_lstlen(st);
	rot = 0;
	while (!can_insert(to_push, ICONT(cp), last_elem(cp)))
	{
		rot++;
		do_one_comm(&cp, NULL, ft_lstnew("ra", 3));
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
/*
static t_list	*try_to_return(t_list **a, t_list **b, int val)
{
	t_list	*comm;

	comm = NULL;
	if (can_insert(val, ICONT(*a), last_elem(*a)))
		add_and_do(&comm, a, b, "pa");
	else if (can_insert(val, ICONT((*a)->next), last_elem((*a)->next)))
	{
		add_and_do(&comm, a, b, "pa");
		add_and_do(&comm, a, b, "sa");
	}
	else if (can_insert(val, last_elem(*a), prelast_elem(*a)))
	{
		add_and_do(&comm, a, b, "rra");
		add_and_do(&comm, a, b, "pa");
		add_and_do(&comm, a, b, "ra");
		add_and_do(&comm, a, b, "ra");
	}
	else if (can_insert(val, ICONT((*a)->next->next), ICONT((*a)->next)))
	{
		add_and_do(&comm, a, b, "ra");
		add_and_do(&comm, a, b, "pa");
		add_and_do(&comm, a, b, "sa");
		add_and_do(&comm, a, b, "rra");
	}
	return (comm);
}*/

t_list	*perform_rot(t_list **a, t_list **b, int to_push, char fl)
{
	t_list	*comm;
	t_list	*new;

	comm = NULL;
	if (fl / 10 == fl % 10)
	{
		while (ICONT(*b) != to_push && !can_insert(to_push, ICONT(*a),
					last_elem(*a)))
		{
//			new = try_to_return(a, b, ICONT(*b));
//			if (new)
//				add_comm(&comm, new);
//			else
				add_and_do(&comm, a, b, fl / 10 == 1 ? "rr" : "rrr");
		}
		while (ICONT(*b) != to_push)
		{
//			new = try_to_return(a, b, ICONT(*b));
//			if (new)
//			{
//				add_comm(&comm, new);
//				if (!can_insert(to_push, ICONT(*a), last_elem(*a)))
//					add_and_do(&comm, a, b, "ra");
//			}
//			else
				add_and_do(&comm, a, b, fl / 10 == 1 ? "rb" : "rrb");
		}
		while (!can_insert(to_push, ICONT(*a), last_elem(*a)))
			add_and_do(&comm, a, b, fl / 10 == 1 ? "ra" : "rra");
	}
	else
	{
		while (ICONT(*b) != to_push)
		{
//			new = try_to_return(a, b, ICONT(*b));
//			if (new)
//				add_comm(&comm, new);
//			else
				add_and_do(&comm, a, b, fl / 10 == 1 ? "rb" : "rrb");
		}
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

	printf("adjust\n");
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
