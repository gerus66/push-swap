/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_a.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 15:50:11 by mbartole          #+#    #+#             */
/*   Updated: 2019/04/02 23:18:35 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

t_list	*get_to_push(int *seq, t_list *st)
{
	int		i;
	int		count;
	t_list	*to_push;

	count = ft_lstlen(st);
	to_push = NULL;
	i = -1;
	while (++i < count)
	{
		if (seq[i] == 0)
			ft_lstadd_back(&to_push,ft_lstnew(st->cont, sizeof(int)));
		st = st->next;
	}
	return (to_push);
}

static void    rotate_seq(int *seq, int len, char fl)
{
	int     mem;
	int     tmp;
	int     i;

	if (fl == -1)
	{
		mem = seq[len - 1];
		i = -1;
		while (++i < len)
		{
			tmp = seq[i];
			seq[i] = mem;
			mem = tmp;
		}
	}
	else
	{
		mem = seq[0];
		i = len;
		while (--i >= 0)
		{
			tmp = seq[i];
			seq[i] = mem;
			mem = tmp;
		}
	}
}

static int	get_rot(t_list *st, int to_push, int i, int len_b, char *fl)
{
	t_list 	*cp;
	int		rot;
	int		ret;
	int		len_a;

	cp = lst_copy(st);
	len_a = ft_lstlen(st);
	rot = 0;
	while (!can_insert(to_push, cp))
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

static t_list	*perform_rot(t_list **a, t_list **b, int to_push, char fl,
		int *seq, int count)
{
	t_list	*comm;

	comm = NULL;
	if (fl / 10 == fl % 10)
	{
		while (ICONT(*b) != to_push && !can_insert(to_push, *a))
		{
			add_and_do(&comm, a, b, fl / 10 == 1 ? "rr" : "rrr");
			rotate_seq(seq, count, fl / 10 == 1 ? 1 : -1);
		}
		while (ICONT(*b) != to_push)
		{
			add_and_do(&comm, a, b, fl / 10 == 1 ? "rb" : "rrb");
			rotate_seq(seq, count, fl / 10 == 1 ? 1 : -1);
		}
		while (!can_insert(to_push, *a))
			add_and_do(&comm, a, b, fl / 10 == 1 ? "ra" : "rra");
	}
	else
	{
		while (ICONT(*b) != to_push)
		{
			add_and_do(&comm, a, b, fl / 10 == 1 ? "rb" : "rrb");
			rotate_seq(seq, count, fl / 10 == 1 ? 1 : -1);
		}
		while (!can_insert(to_push, *a))
			add_and_do(&comm, a, b, fl % 10 == 1 ? "ra" : "rra");
	}
	return (comm);
}

t_list	*adjust_stacks(t_list **a, t_list **b, int *seq, int count)
{
	t_list	*comm;
	t_list	*cp;
	int		i;
	int		rot;
	int		min_rot;
	int		to_push;
	char	fl;
	char	min_fl;

	comm = NULL;
	min_rot = MAX(count, ft_lstlen(*a));
	to_push = 0;
	min_fl = 0;
	cp = *b;
	i = -1;
	while (++i < count)
	{
		if (seq[i])
		{
			rot = get_rot(*a, ICONT(cp), i, count, &fl);
			if (rot < min_rot)
			{
				min_rot = rot;
				to_push = ICONT(cp);
				min_fl = fl;
			}
		}
		cp = cp->next;
	}
	comm = perform_rot(a, b, to_push, min_fl, seq, count);
	return (comm);
}

t_list	*rot_all(t_list **a, t_list **b, int *seq, int count)
{
	t_list	*comm;
	t_list	*all_comm;
	t_list	*cp;
	t_list	*cp2;
	t_list	*cp3;
	int		to_push;
	int		i;
	int		cccount;
	int		prev;

	all_comm = adjust_stacks(a, b, seq, count);
//	printf("adjust stacks:   ");//
//	print_comm(all_comm);//
	i = 0;
	prev = 0;
	while (i < count)
	{
		cp = *b;
		comm = NULL;
		while (!seq[i] && i < count)
		{
			cp = cp->next;
			ft_lstadd_back(&comm, ft_lstnew("rb", 3));
			i++;
		}
		if (i == count)
			break ;
		to_push = ICONT(cp);
		cp3 = *a;
		cccount = 0;
		prev = last_elem(cp3);
		while (!((to_push < ICONT(cp3) && to_push > prev) ||
					(to_push > ICONT(cp3) && to_push > prev && prev > ICONT(cp3)) ||
					(to_push < ICONT(cp3) && ICONT(cp3) < prev)))
		{
			cccount++;
			prev = ICONT(cp3);
			cp3 = cp3->next;
		}
		if (cccount <= ft_lstlen(*a) / 2)
		{
			cp2 = comm;
			while (cccount--)
			{
				if (cp2 && (!ft_strcmp(CCONT(cp2), "rb")))
				{
					ft_memcpy(cp2->cont, (void *)"rr", sizeof(char *));
					cp2 = cp2->next;
				}
				else
					ft_lstadd_back(&comm, ft_lstnew("ra", 3));
			}
		}
		else
		{
			cccount = ft_lstlen(*a) - cccount;
			while (cccount--)
				ft_lstadd_back(&comm, ft_lstnew("rra", 4));
		}
		ft_lstadd_back(&comm, ft_lstnew("pa", 3));
		do_all_comm(a, b, comm, 0);
		add_comm(&all_comm, comm);
		i++;
	}
//	printf("rot all:   ");//
//	print_comm(all_comm);//
	return (all_comm);
}
