/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   magic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 15:52:36 by mbartole          #+#    #+#             */
/*   Updated: 2019/03/14 23:15:41 by mbartole         ###   ########.fr       */
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

	print_stacks(b, sorted_in_b);
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
	printf("insert %d, from top (%d), rot = %d\n", val, from_top, rot);
	return (rot);
}

static t_list	*push_a_to_b(t_list **from, t_list **to, t_list *push,
							t_list *sorted)
{
	t_list	*comm;
	char	from_top;
	int		rot;
	int		rot2;
//	char	fl;

	comm = NULL;
	while (push)
	{
		from_top = 1;
		rot = try_to_insert(ICONT(push), *to, sorted, 1);
		rot2 = try_to_insert(ICONT(push), *to, sorted, 0);
		if (rot > rot2)
		{
			rot = rot2;
			from_top = 0;
		}
//		fl = 0;
		while (ICONT(*from) != ICONT(push))
		{
			if (from_top && ICONT(*to) == ICONT(sorted))
			{
				printf("1\n");
				print_stacks(*to, sorted);
				do_one_comm(&sorted, NULL, ft_lstnew("ra", 3));
//				fl = 1;
			}
			add_and_do(from, to, &comm, 
					ft_lstnew(from_top && rot > 0 ? "rr" : "ra", 3));
			rot = from_top ? rot - 1 : rot;
		}
		while (rot-- > 0)
		{
//			printf("B: %d, sorted: %d\n ", ICONT(*to), ICONT(sorted));
			if (from_top && ICONT(*to) == ICONT(sorted))
			{
				printf("2");
				do_one_comm(&sorted, NULL, ft_lstnew("ra", 3));
			}
			else if (!from_top && last_elem(*to) == last_elem(sorted))
				do_one_comm(&sorted, NULL, ft_lstnew("rra", 3));
			add_and_do(from, to, &comm, ft_lstnew(from_top ? "rb" : "rrb", 3));
		}
		ft_lstadd(&sorted, ft_lstnew((void *)&ICONT(*from), sizeof(int)));
		add_and_do(from, to, &comm, ft_lstnew("pb", 3));
		push = push->next;
	}
	return (comm);
}

static t_list	*push_b_to_a(t_list **a, t_list **b, t_list *push,
							t_list *sorted)
{
	t_list	*comm;
	char	from_top;
	int		rot;
	int		rot2;
	char	fl;

	comm = NULL;
	while (push)
	{
		from_top = 1;
		rot = try_to_insert(ICONT(push), *a, sorted, 1);
		rot2 = try_to_insert(ICONT(push), *a, sorted, 0);
		if (rot > rot2)
		{
			rot = rot2;
			from_top = 0;
		}
		fl = 0;
		while (ICONT(*b) != ICONT(push))
		{
		//	print_stacks(*a, *b);
		//	printf("A: %d, sorted: %d\n ", ICONT(*a), ICONT(sorted));
			if (!fl && from_top && ICONT(*a) == ICONT(sorted))
			{
				do_one_comm(&sorted, NULL, ft_lstnew("ra", 3));
				fl = 1;
			}
			add_and_do(a, b, &comm, 
					ft_lstnew(from_top && rot > 0 ? "rr" : "rb", 3));
			rot = from_top ? rot - 1 : rot;
		}
		while (rot-- > 0)
		{
		//	printf("A: %d, sorted: %d\n ", ICONT(*a), ICONT(sorted));
			if (from_top && ICONT(*a) == ICONT(sorted))
				do_one_comm(&sorted, NULL, ft_lstnew("ra", 3));
			else if (!from_top && last_elem(*a) == last_elem(sorted))
				do_one_comm(&sorted, NULL, ft_lstnew("rra", 3));
			add_and_do(a, b, &comm, ft_lstnew(from_top ? "ra" : "rra", 3));
		}
		ft_lstadd(&sorted, ft_lstnew((void *)&ICONT(*b), sizeof(int)));
		add_and_do(a, b, &comm, ft_lstnew("pa", 3));
		push = push->next;
	}
	return (comm);
}

void	*stacks_magic(t_list **a, t_list **b, t_list **comm)
{
	t_list	*sorted_in_a;
	t_list	*other_in_a;
	t_list	*push_to_b;
	t_list	*sorted_in_b;
	t_list	*other_in_b;
	t_list	*push_to_a;
	t_list	*tmp;

	init_push_and_stay(*a, &other_in_a, &sorted_in_a, 0);
//	if (!other_in_a)
//		return (NULL);
	init_push_and_stay(other_in_a, &tmp, &push_to_b, 0);
	init_push_and_stay(*b, &other_in_b, &sorted_in_b, 0);
	if (!other_in_a && !other_in_b)
		return (NULL);
	init_push_and_stay(other_in_b, &tmp, &push_to_a, 0);
	print_stacks(sorted_in_a, sorted_in_b);
	print_stacks(push_to_b, push_to_a);
	add_comm(comm, push_a_to_b(a, b, push_to_b, sorted_in_b));
	print_stacks(*a, *b);
	add_comm(comm, push_b_to_a(a, b, push_to_a, sorted_in_a));
	print_stacks(*a, *b);
	return ((void *)tmp);
}
