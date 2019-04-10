/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 02:29:38 by mbartole          #+#    #+#             */
/*   Updated: 2019/04/10 02:54:08 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

/*
 * ** push one top element from stack A to somewhere in stack B (optimised)
 * */

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

static t_list	*push_one_last(t_list **a, t_list **b, int *i)
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

t_list	*last(t_list *b)
{
	t_list	*comm;
	t_list	*a;
	t_list	*cp;
	int		*standing;
	int		i;

	a = NULL;
	cp = lst_copy(b);
	comm = NULL;
	choose_sequence(get_diff(cp, 1, 1, ft_lstlen(cp)), &standing, ft_lstlen(cp), 1);
	i = push_a(standing, &a, &cp, &comm);
	while (--i >= 0)
		add_comm(&comm, push_one_last(&a, &cp, &i));
	return (comm);
}
