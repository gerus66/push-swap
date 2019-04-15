/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 17:11:13 by mbartole          #+#    #+#             */
/*   Updated: 2019/04/15 23:39:47 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

static int	helper(t_stacks *all, char *l, char free_line, char f)
{
	if (free_line)
		free(l);
	if (!f)
		exit(clean(ERR_M, all));
	return (f);
}

/*
** do one command [line] on stacks [all.a] ans [all.b]
** if [free_line] - free line before return
** if [comm] is illegal - exit with cleaning [all]
*/

int			do_one_comm(t_stacks *all, char *l, char free_line, char f)
{
	if ((!ft_strcmp(l, "sa") && (f = 11)) ||
			(!ft_strcmp(l, "ss") && (f = 13)))
		swap_stack(&all->a);
	if ((!ft_strcmp(l, "sb") && (f = 12)) ||
			(!ft_strcmp(l, "ss") && (f = 13)))
		swap_stack(&all->b);
	if ((!ft_strcmp(l, "ra") && (f = 31)) ||
			(!ft_strcmp(l, "rr") && (f = 33)))
		rotate_stack(&all->a);
	if ((!ft_strcmp(l, "rb") && (f = 32)) ||
			(!ft_strcmp(l, "rr") && (f = 33)))
		rotate_stack(&all->b);
	if ((!ft_strcmp(l, "rra") && (f = 41)) ||
			(!ft_strcmp(l, "rrr") && (f = 43)))
		r_rotate_stack(&all->a);
	if ((!ft_strcmp(l, "rrb") && (f = 42)) ||
			(!ft_strcmp(l, "rrr") && (f = 43)))
		r_rotate_stack(&all->b);
	if (!ft_strcmp(l, "pa") && (f = 21))
		push_stack(&all->b, &all->a);
	else if (!ft_strcmp(l, "pb") && (f = 22))
		push_stack(&all->a, &all->b);
	return (helper(all, l, free_line, f));
}

/*
** just cycle for do_one_comm
*/

void		do_all_comm(t_stacks *all, t_list *comm)
{
	while (comm)
	{
		do_one_comm(all, CCONT(comm), 0, 0);
		comm = comm->next;
	}
}

/*
** add [name] command to [comm] list
** if smth wrong, exit with clean
*/

void		add_comm(t_stacks *all, t_list **comm, char *name)
{
	t_list	*tmp;

	if (!(tmp = ft_lstnew(name, sizeof(char) * (ft_strlen(name) + 1))))
		exit(clean(ERM_M, all));
	ft_lstadd_back(comm, tmp);
}

/*
** do one command [name] and add it to list [comm]
*/

void		add_and_do(t_stacks *all, t_list **comm, char *name)
{
	add_comm(all, comm, name);
	do_one_comm(all, name, 0, 0);
}
