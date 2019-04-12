/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 02:29:38 by mbartole          #+#    #+#             */
/*   Updated: 2019/04/12 16:50:15 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

/*
** push one top element from stack A to somewhere in stack B (optimised)
*/

static t_list	*one_last_rec(int *i, t_list **a, t_list **b, char reverse)
{
	t_list	*comm;

	comm = NULL;
	if (*i > 0 && can_insert_rev(ICONT((*a)->next), *b))
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
		if (!reverse)
			add_and_do(&comm, a, b, "rb");
		add_and_do(&comm, a, b, "rra");
		(*i)--;
	}
	return (comm);
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
		add_comm(&comm, one_last_rec(i, a, b, reverse));
		add_and_do(&comm, a, b, reverse ? "rrb" : "rb");
	}
	add_and_do(&comm, a, b, "pb");
	return (comm);
}

/*
** algo for last in B is like first algo for A -
** sorted sequence remain in B, other push to B, then return in to B.
** as result, B became reverse sorted
*/

t_list			*last(t_list *b, int count, t_list *origin_a)
{
	t_list	*comm;
	t_list	*a;
	t_list	*cp;
	int		sorted[count];
	int		i;

	if (!(cp = ft_lstcopy(b)))
		exit(clean(ERM_M, (t_list *[]){origin_a, b}, 2));
	get_diff(cp, sorted, 1, 1);
	choose_sequence(sorted, ft_lstlen(cp));
	a = NULL;
	comm = NULL;
	i = push_a(sorted, &a, &cp, &comm);
	while (--i >= 0)
		add_comm(&comm, push_one_last(&a, &cp, &i));
	ft_lstdel(&cp, NULL);
	return (comm);
}
