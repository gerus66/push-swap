/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 01:21:07 by mbartole          #+#    #+#             */
/*   Updated: 2019/04/10 01:34:02 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

/*
** push one top element from stack B to somewhere in stack A (optimised)
*/

static t_list	*push_one_ba(t_list **a, t_list **b)
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

static t_list	*adjust_stacks_last(t_list **a, t_list **b)
{
	t_list	*comm;
	t_list	*cp;
	int		i;
	int		rot;
	int		min_rot;
	int		to_push;
	int		last_to_push;
	int		len_b;
	char	fl;
	char	min_fl;

	len_b = ft_lstlen(*b);
	comm = NULL;
	min_rot = 2 * (ft_lstlen(*b) + ft_lstlen(*a));
	to_push = 0;
	last_to_push = last_elem(*b);
	min_fl = 0;
	cp = *b;
	i = -1;
	while (++i < len_b)
	{
		/*adjust stacks to each other*/
		rot = get_rot(*a, ICONT(cp), i, len_b, &fl);
		/*last rotation of stack A to 0*/
		rot += MIN(last_to_push, (len_b + ft_lstlen(*a) - last_to_push));
		/*rotation of stack A during push*/
		rot += (ICONT(cp) > last_to_push) ?
			len_b + ft_lstlen(*a) - ICONT(cp) + last_to_push :
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
	comm = perform_rot(a, b, to_push, min_fl);
	return (comm);
}

/*
** push elements back to sorted A from reverse sorted B (until the end)
*/

t_list	*back_to_a_last(t_list **a, t_list **b)
{
	t_list	*comm;
	int		len_b;

	comm = adjust_stacks_last(a, b);
	len_b = ft_lstlen(*b);
	while (--len_b >= 0)
		add_comm(&comm, push_one_ba(a, b));
	return (comm);
}
