/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 01:21:07 by mbartole          #+#    #+#             */
/*   Updated: 2019/04/13 17:35:06 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

/*
** push one top element from stack B to somewhere in stack A (optimised)
*/

static void		push_one_ba(t_stacks *all)
{
	t_list	*cp;
	int		rot;
	char	reverse;

	cp = all->a;
	rot = 0;
	while (!can_insert(ICONT(all->b), ICONT(cp), last_elem(cp)) &&
			cp->next && ++rot)
		cp = cp->next;
	reverse = rot > ft_lstlen(all->a) / 2 ? 1 : 0;
	if (reverse)
		rot = ft_lstlen(all->a) - rot;
	while (--rot >= 0)
		add_and_do(all, &all->local_comm, reverse ? "rra" : "ra");
	add_and_do(all, &all->local_comm, "pa");
	all->len_a++;
	all->len_b--;
}

/*
** adjust stacks to each other +
** last rotation of stack A to 0 +
** rotation of stack A during push
** rot[0] rot
** rot[1] min_rot
** fl[0] fl
** fl[1] min_fl
*/

static void		adjust_stacks_last(t_stacks *all)
{
	t_list	*cp;
	int		i;
	int		rot;
	int		min_rot;
	int		to_push;
	int		last;
	char	fl;
	char	min_fl;

	rot = 2 * (ft_lstlen(all->b) + ft_lstlen(all->a));
	to_push = 0;
	last = last_elem(all->b);
	min_fl = 0;
	cp = all->b;
	i = -1;
	while (++i < all->len_b)
	{
		rot = get_rot(all->a, (int[]){ICONT(cp), i, all->len_b}, &fl) +
		MIN(last, (all->len_b + ft_lstlen(all->a) - last)) + (ICONT(cp) > last)
		? all->len_b + ft_lstlen(all->a) - ICONT(cp) + last : last - ICONT(cp);
		if (rot < min_rot)
		{
			min_rot = rot;
			to_push = ICONT(cp);
			min_fl = fl;
		}
		last = ICONT(cp);
		cp = cp->next;
	}
	perform_rot(all, to_push, min_fl);
}

/*
** push elements back to sorted A from reverse sorted B (until the end)
*/

void			last_push(t_stacks *all)
{
	if (!all->len_b)
		return ;
	adjust_stacks_last(all);
	while (all->len_b)
		push_one_ba(all);
	ft_lstadd_back(&all->comm, all->local_comm);
	all->local_comm = NULL;
}
