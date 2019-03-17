/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   magic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 15:52:36 by mbartole          #+#    #+#             */
/*   Updated: 2019/03/16 20:50:27 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

char	can_insert(int val, t_list *st)
{
	if ((val < ICONT(st) && val > last_elem(st)) ||
		(val > ICONT(st) && val > last_elem(st) && ICONT(st) < last_elem(st))
		|| (val < ICONT(st) && ICONT(st) < last_elem(st)))
		return (1);
	return (0);
}

void	add_and_do(t_list **a, t_list **b, t_list **comm, t_list *add)
{
			ft_lstadd_back(comm, add);
			do_one_comm(a, b, add);
}

static int	try_to_insert(int val, t_list *b, t_list *sorted_in_b, char from_top)
{
	int	rot;
	t_list	*cp_b;
	t_list	*cp_sort;

//	printf("try to insert:\n");
//	print_stacks(b, sorted_in_b);
	cp_b = lst_copy(b);
	cp_sort = lst_copy(sorted_in_b);
	rot = 0;
	if (from_top)
		while (!can_insert(val, cp_sort))
		{
			if (ICONT(cp_b) == ICONT(cp_sort))
				do_one_comm(&cp_sort, NULL, ft_lstnew("ra", 3));
			do_one_comm(&cp_b, NULL, ft_lstnew("ra", 3));
			rot++;
		}
	else
		while (!can_insert(val, cp_sort))
		{
			if (last_elem(cp_b) == last_elem(cp_sort))
				do_one_comm(&cp_sort, NULL, ft_lstnew("rra", 3));
			do_one_comm(&cp_b, NULL, ft_lstnew("rra", 3));
			rot++;
		}
	ft_lstdel(&cp_b, NULL);
	ft_lstdel(&cp_sort, NULL);
//	printf("insert %d, from top (%d), rot = %d\n", val, from_top, rot);
	return (rot);
}

static t_list	*push_a_to_b(t_list **a, t_list **b, t_list *push, t_list **sorted)
{
	t_list	*comm;
	char	from_top;
	int		rot;
	int		i;

	comm = NULL;
	while (push)
	{
//		printf("A,    B\n");//
//		print_stacks(*a, *b);//
//		printf("push, sorted\n");//
//		print_stacks(push, *sorted);//
		from_top = 0;
		rot = try_to_insert(ICONT(push), *b, *sorted, 0);
		i = try_to_insert(ICONT(push), *b, *sorted, 1);
		if (i < rot && (from_top = 1))
			rot = i;
//		printf("(%d)from_top - %d\n", from_top, rot);//
		while (ICONT(*a) != ICONT(push))
		{
			if (from_top && rot > 0)
			{
				if (ICONT(*b) == ICONT(*sorted))
					do_one_comm(sorted, NULL, ft_lstnew("ra", 3));
				add_and_do(a, b, &comm, ft_lstnew("rr", 3));
				rot--;
			}
			else
				add_and_do(a, b, &comm, ft_lstnew("ra", 3));
		}
		while (rot > 0)
		{
			if (from_top && ICONT(*b) == ICONT(*sorted))
				do_one_comm(sorted, NULL, ft_lstnew("ra", 3));
			else if (!from_top && last_elem(*b) == last_elem(*sorted))
				do_one_comm(sorted, NULL, ft_lstnew("rra", 3));
			add_and_do(a, b, &comm, ft_lstnew(from_top ? "rb" : "rrb", 3));
			rot--;
		}
		ft_lstadd(sorted, ft_lstnew((void *)&ICONT(*a), sizeof(int)));
		add_and_do(a, b, &comm, ft_lstnew("pb", 3));
		push = push->next;
	}
//		printf("A,    B\n");//
//		print_stacks(*a, *b);//
//		printf("push, sorted\n");//
//		print_stacks(push, *sorted);//
	print_comm(comm);//
	return (comm);
}

static t_list	*push_b_to_a(t_list **a, t_list **b, t_list *push, t_list **sorted)
{
	t_list	*comm;
	char	from_top;
	int		rot;
	int		i;

	comm = NULL;
	while (push)
	{
//		printf("A,    B\n");//
//		print_stacks(*a, *b);//
//		printf("push, sorted\n");//
//		print_stacks(push, *sorted);//
		from_top = 0;
		rot = try_to_insert(ICONT(push), *a, *sorted, 0);
		i = try_to_insert(ICONT(push), *a, *sorted, 1);
		if (i < rot && (from_top = 1))
			rot = i;
//		printf("(%d)from_top - %d\n", from_top, rot);//
		while (ICONT(*b) != ICONT(push))
		{
			if (from_top && rot > 0)
			{
				if (ICONT(*a) == ICONT(*sorted))
					do_one_comm(sorted, NULL, ft_lstnew("ra", 3));
				add_and_do(a, b, &comm, ft_lstnew("rr", 3));
				rot--;
			}
			else
				add_and_do(a, b, &comm, ft_lstnew("rb", 3));
		}
		while (rot > 0)
		{
			if (from_top && ICONT(*a) == ICONT(*sorted))
				do_one_comm(sorted, NULL, ft_lstnew("ra", 3));
			else if (!from_top && last_elem(*a) == last_elem(*sorted))
				do_one_comm(sorted, NULL, ft_lstnew("rra", 3));
			add_and_do(a, b, &comm, ft_lstnew(from_top ? "ra" : "rra", 3));
			rot--;
		}
		ft_lstadd(sorted, ft_lstnew((void *)&ICONT(*b), sizeof(int)));
		add_and_do(a, b, &comm, ft_lstnew("pa", 3));
		push = push->next;
	}
//		printf("A,    B\n");//
//		print_stacks(*a, *b);//
//		printf("push, sorted\n");//
//		print_stacks(push, *sorted);//
	print_comm(comm);//
	return (comm);
}

void	*stacks_magic(t_list **a, t_list **b, t_list **comm, t_list *sorted_in_a, t_list *sorted_in_b)
{
//	t_list	*sorted_in_a;
	t_list	*other_in_a;
	t_list	*push_to_b;
//	t_list	*sorted_in_b;
	t_list	*other_in_b;
	t_list	*push_to_a;
	t_list	*tmp;

	other_in_a = NULL;
	init_push_and_stay(*a, &other_in_a, &sorted_in_a, 0);
	tmp = NULL;
	push_to_b = NULL;
	init_push_and_stay(other_in_a, &tmp, &push_to_b, 0);
	other_in_b = NULL;
	init_push_and_stay(*b, &other_in_b, &sorted_in_b, 0);
	if (!other_in_a && !other_in_b)
		return (NULL);
	tmp = NULL;
	push_to_a = NULL;
	init_push_and_stay(other_in_b, &tmp, &push_to_a, 0);
//	printf("sorted:\n");
//	print_stacks(sorted_in_a, sorted_in_b);
//	printf("to push:\n");
//	print_stacks(push_to_b, push_to_a);
	add_comm(comm, push_a_to_b(a, b, push_to_b, &sorted_in_b));
//	printf("stacks before:\n");
//	print_stacks(*a, *b);
	add_comm(comm, push_b_to_a(a, b, push_to_a, &sorted_in_a));
//	printf("stacks after:\n");
//	print_stacks(*a, *b);
	return (stacks_magic(a, b, comm, sorted_in_a, sorted_in_b));
}
