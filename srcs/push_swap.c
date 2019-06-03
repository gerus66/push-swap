/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 14:28:39 by mbartole          #+#    #+#             */
/*   Updated: 2019/04/17 18:59:38 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

static void		print_comm(t_list *comm)
{
	t_list	*tmp;

	tmp = comm;
	while (comm)
	{
		write(1, CCONT(comm), ft_strlen(CCONT(comm)));
		write(1, "\n", 1);
		comm = comm->next;
	}
}

/*
** first check on 2 arguments
*/

static int		first_check(t_stacks *all)
{
	if (all->len_a == 1)
		exit(clean("", all));
	if (all->len_a == 2)
	{
		if (ICONT(all->a) > ICONT(all->a->next))
			exit(clean("sa\n", all));
		exit(clean("", all));
	}
	return (0);
}

static void		push_b(t_stacks *all, int count)
{
	int		i;
	int		standing[count];

	get_diff(all->a, standing, 1, 0);
	choose_sequence(standing, all->len_a, all);
	i = -1;
	while (++i < count)
	{
		if (standing[i] == 0 && ++all->len_b && --all->len_a)
			add_comm(all, &all->comm, "pb");
		else if (standing[i] == -1)
		{
			add_comm(all, &all->comm, "rra");
			add_comm(all, &all->comm, "sa");
			add_comm(all, &all->comm, "ra");
			add_comm(all, &all->comm, "ra");
		}
		else
			add_comm(all, &all->comm, "ra");
	}
	cut_tail(&all->comm, "ra");
	improve_comm_dub(&all->comm);
	do_all_comm(all, all->comm);
}

int				main(int argc, char **argv)
{
	t_stacks	all;
	t_list		*new_comm;

	if (argc < 2)
		return (0);
	init_all(&all, argv, argc - 1, 1);
	first_check(&all);
	push_b(&all, all.len_a);
	new_comm = NULL;
	while (ft_lstlen(all.b) > 5)
	{
		back_to_a(&all);
		if (ft_lstlen((new_comm = last(&all, ft_lstlen(all.b)))) < all.len_a)
			break ;
		ft_lstdel(&new_comm, NULL);
	}
	if (!new_comm)
		new_comm = last(&all, ft_lstlen(all.b));
	do_all_comm(&all, new_comm);
	ft_lstadd_back(&all.comm, new_comm);
	last_push(&all);
	improve_comm_swap(&all.comm);
	improve_comm_dub(&all.comm);
	print_comm(all.comm);
	return (clean("", &all));
}
