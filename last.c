/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 02:29:38 by mbartole          #+#    #+#             */
/*   Updated: 2019/04/15 18:14:08 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

static t_list	*one_last_rec(int *i, t_stacks *copy, char reverse)
{
	t_list	*comm;

	comm = NULL;
	if (*i > 0 && can_insert_rev(ICONT(copy->a->next), copy->b))
	{
		add_and_do(copy, &comm, "sa");
		add_and_do(copy, &comm, "pb");
		(*i)--;
		if (!reverse)
			add_and_do(copy, &comm, "rb");
	}
	if (*i > 1 && can_insert_rev(ICONT(copy->a->next->next), copy->b))
	{
		add_and_do(copy, &comm, "ra");
		add_and_do(copy, &comm, "sa");
		add_and_do(copy, &comm, "pb");
		if (!reverse)
			add_and_do(copy, &comm, "rb");
		add_and_do(copy, &comm, "rra");
		(*i)--;
	}
	return (comm);
}

/*
** push one top element from stack A to sorted stack B (optimised)
*/

static t_list	*push_one_last(t_stacks *copy, int *i)
{
	t_list	*comm;
	t_list	*cp;
	int		rot;
	char	reverse;
	int		len_b;

	comm = NULL;
	len_b = ft_lstlen(copy->b);
	cp = copy->b;
	rot = 0;
	while (!can_insert_rev(ICONT(copy->a), cp) && cp->next && ++rot)
		cp = cp->next;
	reverse = rot > len_b / 2 ? 1 : 0;
	if (reverse)
		rot = len_b - rot;
	while (--rot >= 0)
	{
		ft_lstadd_back(&comm, one_last_rec(i, copy, reverse));
		add_and_do(copy, &comm, reverse ? "rrb" : "rb");
	}
	add_and_do(copy, &comm, "pb");
	return (comm);
}

/*
** remain sorted part in stack B, others push to stack A
** return number of pushed to A elems
*/

static t_list	*push_a(int *standing, t_stacks *copy)
{
	int		i;
	int		count;
	t_list	*tmp;
	t_list	*comm;

	comm = NULL;
	count = ft_lstlen(copy->b);
	i = -1;
	tmp = copy->b;
	while (++i < count)
	{
		if (standing[i] == 0)
			add_comm(copy, &comm, "pa");
		else if (standing[i] == -1)
		{
			add_comm(copy, &comm, "rrb");
			add_comm(copy, &comm, "sb");
			add_comm(copy, &comm, "rb");
			add_comm(copy, &comm, "rb");
		}
		else
			add_comm(copy, &comm, "rb");
		tmp = tmp->next;
	}
	return (comm);
}

/*
** algo for last in B is like first algo for A -
** sorted sequence remain in B, other push to B, then return in to B.
** as result, B became reverse sorted
*/

t_list			*last(t_stacks *origin, int count)
{
	t_list		*comm;
	int			sorted[count];
	int			i;
	t_stacks	copy;

	if (!origin->b)
		return (NULL);
	if (!(copy.b = ft_lstcopy(origin->b)))
		exit(clean(ERM_M, origin));
	get_diff(copy.b, sorted, 1, 1);
	choose_sequence(sorted, ft_lstlen(copy.b), origin);
	copy.a = NULL;
	copy.comm = NULL;
	comm = push_a(sorted, &copy);
	cut_tail(&comm, "rb");
	improve_comm_dub(&comm);
	do_all_comm(&copy, comm);
	i = ft_lstlen(copy.a);
	while (--i >= 0)
		ft_lstadd_back(&comm, push_one_last(&copy, &i));
	clean("", &copy);
	return (comm);
}
