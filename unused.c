/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 14:28:39 by mbartole          #+#    #+#             */
/*   Updated: 2019/02/08 12:44:47 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

#define I_MAX 2147483647
#define I_MIN -2147483648

#define ABS(x) ((x) < 0 ? -(x) : (x))

/*
static int	check_stacks(t_list *st, t_list *tmp)
{
	int	fl;
	ssize_t	prev;

	if (!st || !st->next || tmp)
		return (0);
	fl = 1;
	prev = *((ssize_t *)st->cont);
	st = st->next;
	while (st)
	{
		if (*((ssize_t *)st->cont) < prev)
			return (0);
		else if (*((ssize_t *)st->cont) == prev)
			exit(clean(ERR_M));//TODO
		prev = *((ssize_t *)st->cont);
		st = st->next;
	}
	return (1);
}*/
/*
static int	middle_of_three(int a, int b, int c)
{
	if ((a > b && b > c) || (c > b && b > a))
		return (b);
	if ((b > a && a > c) || (c > a && a > b))
		return (a);
	return (c);
}*/
/*
static int	find_pivot(int *st, int size)
{
	int	i_max;
	int	i_min;
	int	i;
	int	new[size - 2];

	if (size == 1)
		return (st[0]);
	if (size == 2)
		return (st[0] > st[1] ? st[0] : st[1]);
	if (size == 3)
		return (middle_of_three(st[0], st[1], st[2]));
	i_min = 0;
	i_max = i_min;
	i = -1;
	while (++i < size)
	{
		if (st[i] < st[i_min])
			i_min = i;
		if (st[i] > st[i_max])
			i_max = i;
	}
	i = 0;
	int j = 0;
	while (i < size)
	{
		if (i != i_min && i != i_max)
			new[j++] = st[i];
		i++;
	}
	return (find_pivot(new, size - 2));
}*/

/*
static void	stacks_magic(t_list **a, t_list **b, t_list **comm, int count)
{
	int ar[count];
	int	p;
	int	i;

	print_stacks(*a, *b);//--
	printf("count = %d, first /%c/\n", count, first);//--
	list_to_array(*a, ar, count);
	p = find_pivot(ar, count);
	printf("pivot = %d\n", p);//--
	i = -1;
	while (++i < count)
	{
		if (ICONT(*a) < p)
		{
			push_stack(a, b);
			ft_lstadd_back(comm, ft_lstnew("pb", 3));
			stacks_paral(t_list **a, t_list **b);
		}
		else
		{
			rotate_stack(a);
			ft_lstadd_back(comm, ft_lstnew("ra", 3));
		}
		print_stacks(*a, *b);//--
	}
	printf("len of a: %d || len of b: %d\n", len_act, len_other);//--
	stacks_magic(a, b, comm, len_act, 'a');
	stacks_magic(b, a, comm, len_other, 'b');
}*/
/*
static void	print_comm(t_list *comm)
{
	while (comm)
	{
		ft_putstr((char *)comm->cont);
		if ((comm = comm->next))
			ft_putchar('\n');
	}
}*/
