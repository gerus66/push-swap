/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 14:28:39 by mbartole          #+#    #+#             */
/*   Updated: 2019/02/04 15:06:15 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

#define I_MAX 2147483647
#define I_MIN -2147483648

//#define INT_CONT(x) (*((int *)(x)->cont))

static	int	clean(char *msg)
{
	ft_putstr(msg);
	return (0);
}

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
}

//TODO to define
/*static int	lst_cmp(t_list *l1, t_list *l2)
{
	return ((*(ssize_t *)(l1->cont) - *(ssize_t *)(l2->cont)));
}*/

static int	middle_of_three(int a, int b, int c)
{
	if ((a > b && b > c) || (c > b && b > a))
		return (b);
	if ((b > a && a > c) || (c > a && a > b))
		return (a);
	return (c);
}

static int	find_pivot(int *st, int size)
{
	int	i_max;
	int	i_min;
	int	i;
	int	new[size - 2];

	if (size == 1)
		return (st[0]);
	if (size == 2)
	//{
	//	if (max_pivot)
			return (st[0] > st[1] ? st[0] : st[1]);
	//	else
	//		return (st[0] > st[1] ? st[1] : st[0]);
//	}
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
}

static void	list_to_array(t_list *st, int *ar, int count)
{
	int	i;

	i = -1;
	while (st && ++i < count)
	{
		ar[i] = ICONT(st);
		st = st->next;
	}
}

static void	sort_three(t_list **st)
{
	st++;
}

//static void	sort_two(t_list *st)

static void	stacks_paral(t_list **a, t_list **b)
{
	if ()
}

static void	stacks_magic(t_list **a, t_list **b, t_list **comm, int count)
{
	int ar[count];
	int	p;
	int	i;
//	int	len_act;
//	int	len_other;

	print_stacks(*a, *b);//--
	printf("count = %d, first /%c/\n", count, first);//--
/*	if (count == 2)
	{
		if ((ICONT(*a) > ICONT((*a)->next) && first == 'a') || (ICONT(*a) < ICONT((*a)->next) && first == 'b'))
			swap_stack(a);
		if (first == 'b')
			while (count--)
			{
				push_stack(a, b);
				ft_lstadd_back(comm, ft_lstnew("pa", 3));
			}
		return ;
	}
	if (count == 3)//TODO
	{
		sort_three(a);//TODO
		return ;
	}*/
	list_to_array(*a, ar, count);
	p = find_pivot(ar, count);
	printf("pivot = %d\n", p);//--
	i = -1;
	while (++i < count)
	{
//		printf("/%d/\n", ICONT(*a));//--
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
}

static void	print_comm(t_list *comm)
{
	while (comm)
	{
		ft_putstr((char *)comm->cont);
		if ((comm = comm->next))
			ft_putchar('\n');
	}
}


int		atoi_check(char *s)
{
	ssize_t	res;
	char	sign;

	res = 0;
	sign = (*s == '-' ? -1 : 1);
	if (*s == '-' || *s == '+')
		s++;
	while (*s)
	{
		if (*s >= '0' && *s <= '9')
			res = res * 10 + *s - 48;
		else
			exit(clean(ERR_M));//TODO
		s++;
	}
	res *= sign;
	if (res > I_MAX || res < I_MIN)
		exit(clean(ERR_M));//TODO
	return ((int)res);
}

int			main(int argc, char **argv)
{
	t_list	*a;
	t_list	*b;
	t_list	*comm;
	int		tmp;
//	int		int_st[argc - 1];
	int		i;

	if (argc < 3)
		return (0);
	i = argc - 1;
	while (--i >= 0)
	{
		tmp = atoi_check(argv[i + 1]);
//		int_st[i] = atoi_check(argv[i + 1]);
		ft_lstadd(&a, ft_lstnew((void *)&tmp, sizeof(int)));
	}
//	printf("pivot value %d\n", find_pivot(int_st, argc - 1, 0));//
	b = NULL;
	comm = NULL;
//	print_stacks(a, b);
	check_stacks(a, b);
	stacks_magic(&a, &b, &comm, argc - 1, 'a');
	print_comm(comm);
}
