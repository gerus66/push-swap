/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 01:21:07 by mbartole          #+#    #+#             */
/*   Updated: 2019/04/15 13:55:09 by mbartole         ###   ########.fr       */
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

static void		adjust_stacks_last(t_stacks *all, int last)
{
	t_list	*cp;
	int		i;
	int		rot[2];
	int		to_push;
	char	fl[2];

	rot[1] = 2 * (all->len_b + all->len_a);
	to_push = 0;
	fl[1] = 0;
	cp = all->b;
	i = -1;
	while (++i < all->len_b)
	{
		rot[0] = get_rot(all->a, (int[]){ICONT(cp), i, all->len_b}, &fl[0]) +
		MIN(last, (all->len_b + ft_lstlen(all->a) - last)) + (ICONT(cp) > last
		? all->len_b + ft_lstlen(all->a) - ICONT(cp) + last : last - ICONT(cp));
		if (rot[0] < rot[1] && (fl[1] = fl[0]))
		{
			rot[1] = rot[0];
			to_push = ICONT(cp);
		}
		last = ICONT(cp);
		cp = cp->next;
	}
	perform_rot(all, to_push, fl[1]);
}

/*
** push elements back to sorted A from reverse sorted B (until the end)
** then rotate sorted stack A to the start
*/

void			last_push(t_stacks *all)
{
	if (!all->len_b)
		return ;
	adjust_stacks_last(all, last_elem(all->b));
	while (all->len_b)
		push_one_ba(all);
	if (all->len_a - ICONT(all->a) < all->len_a / 2)
		while (ICONT(all->a) != 0)
			add_and_do(all, &all->local_comm, "ra");
	else
		while (ICONT(all->a) != 0)
			add_and_do(all, &all->local_comm, "rra");
	ft_lstadd_back(&all->comm, all->local_comm);
	all->local_comm = NULL;
}
