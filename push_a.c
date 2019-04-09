/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_a.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 15:50:11 by mbartole          #+#    #+#             */
/*   Updated: 2019/04/09 22:05:03 by mbartole         ###   ########.fr       */
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
//			printf(" S ");
			(*i)--;
			if (!reverse)
				add_and_do(comm, a, b, "rb");
		}
		if (*i > 1 && can_insert_rev(ICONT((*a)->next->next), *b))
		{
			add_and_do(comm, a, b, "ra");
			add_and_do(comm, a, b, "sa");
			add_and_do(comm, a, b, "pb");
//			printf(" SS ");
//			one_last_rec(i, a, b, comm, reverse);
			if (!reverse)
			{
				add_and_do(comm, a, b, "rb");
//				one_last_rec(i, a, b, comm, reverse);
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

	comm = NULL;
	cp = *b;
	rot = 0;
	while (!can_insert_rev(ICONT(*a), cp) && cp->next && ++rot)
		cp = cp->next;
	reverse = rot > ft_lstlen(*b) / 2 ? 1 : 0;
	if (reverse)
		rot = ft_lstlen(*b) - rot;
	while (--rot >= 0)
	{
	/*	if (*i > 0 && can_insert_rev(ICONT((*a)->next), *b))
		{
			add_and_do(&comm, a, b, "sa");
			add_and_do(&comm, a, b, "pb");
			(*i)--;
			if (!reverse)
				add_and_do(&comm, a, b, "rb");
		}
		if (*i > 1 && can_insert_rev(ICONT((*a)->next->next), *b))
		{
			add_and_do(&comm, a, b, "ra");
			add_and_do(&comm, a, b, "sa");
			add_and_do(&comm, a, b, "pb");
			add_and_do(&comm, a, b, "rra");
			(*i)--;
			if (!reverse)
				add_and_do(&comm, a, b, "rb");
		}*/
		one_last_rec(i, a, b, &comm, reverse);
		add_and_do(&comm, a, b, reverse ? "rrb" : "rb");
	}
	add_and_do(&comm, a, b, "pb");
	return (comm);
}

/*
** push one top element from stack B to somewhere in stack A (optimised)
*/

t_list	*push_one_ba(t_list **a, t_list **b)
{
	t_list	*comm;
	t_list	*cp;
	int		rot;
	char	reverse;

	comm = NULL;
	cp = *a;
	rot = 0;
	while (!can_insert(ICONT(*b), ICONT(cp), last_elem(cp)) &&
			cp->next && ++rot)
		cp = cp->next;
	reverse = rot > ft_lstlen(*a) / 2 ? 1 : 0;
	if (reverse)
		rot = ft_lstlen(*a) - rot;
	while (--rot >= 0)
		add_and_do(&comm, a, b, reverse ? "rra" : "ra");
	add_and_do(&comm, a, b, "pa");
	return (comm);
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
	//	if (final)
	//		return (ret + last_elem(st));
	return (ret);
}

static t_list	*try_to_return(t_list **a, t_list **b, int val, int **seq,
		int *count)
{
	t_list	*comm;

	comm = NULL;
	if (can_insert(val, ICONT(*a), last_elem(*a)))
	{
		add_and_do(&comm, a, b, "pa");
		(*seq)++;
		(*count)--;
//		printf(" +%d ", val);
	}
	else if (can_insert(val, ICONT((*a)->next), last_elem((*a)->next)))
	{
		add_and_do(&comm, a, b, "pa");
		add_and_do(&comm, a, b, "sa");
		(*seq)++;
		(*count)--;
//		printf(" s%d ", val);
	}
	else if (can_insert(val, last_elem(*a), prelast_elem(*a)))
	{
		add_and_do(&comm, a, b, "rra");
		add_and_do(&comm, a, b, "pa");
		add_and_do(&comm, a, b, "ra");
		add_and_do(&comm, a, b, "ra");
		(*seq)++;
		(*count)--;
//		printf(" s%d ", val);
	}
	else if (can_insert(val, ICONT((*a)->next->next), ICONT((*a)->next)))
	{
		add_and_do(&comm, a, b, "ra");
		add_and_do(&comm, a, b, "pa");
		add_and_do(&comm, a, b, "sa");
		add_and_do(&comm, a, b, "rra");
		(*seq)++;
		(*count)--;
	}
	return (comm);
}

static t_list	*perform_rot(t_list **a, t_list **b, int to_push, char fl,
		int **seq, int *count)
{
	t_list	*comm;
	t_list	*new;

	comm = NULL;
	if (fl / 10 == fl % 10)
	{
		while (ICONT(*b) != to_push && !can_insert(to_push, ICONT(*a),
					last_elem(*a)))
		{
			new = try_to_return(a, b, ICONT(*b), seq, count);
			if (new)
				add_comm(&comm, new);
			else
			{
				add_and_do(&comm, a, b, fl / 10 == 1 ? "rr" : "rrr");
				rotate_seq(*seq, *count, fl / 10 == 1 ? 1 : -1);
			}
		}
		while (ICONT(*b) != to_push)
		{
			new = try_to_return(a, b, ICONT(*b), seq, count);
			if (new)
			{
				add_comm(&comm, new);
				if (!can_insert(to_push, ICONT(*a), last_elem(*a)))
					add_and_do(&comm, a, b, "ra");
			}
			else
			{
				add_and_do(&comm, a, b, fl / 10 == 1 ? "rb" : "rrb");
				rotate_seq(*seq, *count, fl / 10 == 1 ? 1 : -1);
			}
		}
		while (!can_insert(to_push, ICONT(*a), last_elem(*a)))
			add_and_do(&comm, a, b, fl / 10 == 1 ? "ra" : "rra");
	}
	else
	{
		while (ICONT(*b) != to_push)
		{
			new = try_to_return(a, b, ICONT(*b), seq, count);
			if (new)
				add_comm(&comm, new);
			else
			{
				add_and_do(&comm, a, b, fl / 10 == 1 ? "rb" : "rrb");
				rotate_seq(*seq, *count, fl / 10 == 1 ? 1 : -1);
			}
		}
		while (!can_insert(to_push, ICONT(*a), last_elem(*a)))
			add_and_do(&comm, a, b, fl % 10 == 1 ? "ra" : "rra");
	}
	return (comm);
}

t_list	*adjust_stacks(t_list **a, t_list **b, int **seq, int *count)
{
	t_list	*comm;
	t_list	*cp;
	int		i;
	int		rot;
	int		min_rot;
	int		to_push;
	char	fl;
	char	min_fl;

//			print_seq(*seq, ft_lstlen(*b));
	comm = NULL;
	min_rot = MAX(ft_lstlen(*b), ft_lstlen(*a));
	to_push = 0;
	min_fl = 0;
	cp = *b;
	i = 0;
	while (cp)
	{
		if ((*seq)[i])
		{
			rot = get_rot(*a, ICONT(cp), i, ft_lstlen(*b), &fl);
	//		printf("/%d/ ", rot);
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
//	printf("to push %d |", to_push);
	comm = perform_rot(a, b, to_push, min_fl, seq, count);
//	printf("adjust stacks:	");
//	print_comm(comm);
//	print_stacks(*a, *b);
	return (comm);
}

t_list	*adjust_stacks_last(t_list **a, t_list **b, int **seq, int *count)
{
	t_list	*comm;
	t_list	*cp;
	int		i;
	int		rot;
	int		min_rot;
	int		to_push;
	int		last_to_push;
	char	fl;
	char	min_fl;

	comm = NULL;
	min_rot = 2 * (*count + ft_lstlen(*a));
	to_push = 0;
	last_to_push = last_elem(*b);
	min_fl = 0;
	cp = *b;
	i = -1;
	while (++i < *count)
	{
		//adjust stacks to each other
		rot = get_rot(*a, ICONT(cp), i, *count, &fl);
		//last rotation of stack A to 0
		rot += MIN(last_to_push, (*count + ft_lstlen(*a) - last_to_push));
		//rotation of stack A during push
		rot += (ICONT(cp) > last_to_push) ?
			*count + ft_lstlen(*a) - ICONT(cp) + last_to_push :
			last_to_push - ICONT(cp);
		if (rot < min_rot)
		{
			min_rot = rot;
			to_push = ICONT(cp);
			min_fl = fl;
		}
		last_to_push = ICONT(cp);
		cp = cp->next;
	}
	comm = perform_rot(a, b, to_push, min_fl, seq, count);
	return (comm);
}


t_list	*rot_all(t_list **a, t_list **b, int *seq, int count, char final)
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

	if (final)
		all_comm = adjust_stacks_last(a, b, &seq, &count);
	else
		all_comm = adjust_stacks(a, b, &seq, &count);
	//	printf("adjust stacks:   ");//
	//	print_comm(all_comm);//
	i = 0;
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
	//		printf("rot all:   ");//
	//		print_comm(all_comm);//
	return (all_comm);
}

char static	empty_seq(int *seq, int count)
{
	while (--count >= 0)
		if (seq[count])
			return (0);
	return (1);
}

void	print_seq(int *seq, int count)
{
	int i = -1;
	while (++i < count)
		printf("%2d ", seq[i]);
	printf("\n");
}

t_list	*new_rot_all(t_list **a, t_list **b, int *seq, int count)
{
	t_list	*comm;
	t_list	*new;

//	print_seq(seq, ft_lstlen(*b));
	comm = NULL;
	while (1)
	{
		new = adjust_stacks(a, b, &seq, &count);
//		print_comm(new);//
		add_comm(&comm, new);
		add_and_do(&comm, a, b, "pa");
		seq++;
		count--;
		if (empty_seq(seq, count))
			return (comm);
	}
}
