/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 17:11:13 by mbartole          #+#    #+#             */
/*   Updated: 2019/04/17 13:39:37 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

int			code_comm(char *l, char bef, char fl)
{
	if (!ft_strcmp(l, "sa"))
		fl = 11;
	else if (!ft_strcmp(l, "ss"))
		fl = 13;
	else if (!ft_strcmp(l, "sb"))
		fl = 12;
	else if ((!ft_strcmp(l, "ra") && !bef) || (!ft_strcmp(l, "rra") && bef))
		fl = 31;
	else if ((!ft_strcmp(l, "rr") && !bef) || (!ft_strcmp(l, "rrr") && bef))
		fl = 33;
	else if ((!ft_strcmp(l, "rb") && !bef) || (!ft_strcmp(l, "rrb") && bef))
		fl = 32;
	else if ((!ft_strcmp(l, "rra") && !bef) || (!ft_strcmp(l, "ra") && bef))
		fl = 41;
	else if ((!ft_strcmp(l, "rrr") && !bef) || (!ft_strcmp(l, "rr") && bef))
		fl = 43;
	else if ((!ft_strcmp(l, "rrb") && !bef) || (!ft_strcmp(l, "rb") && bef))
		fl = 42;
	else if ((!ft_strcmp(l, "pa") && !bef) || (!ft_strcmp(l, "pb") && bef))
		fl = 21;
	else if ((!ft_strcmp(l, "pb") && !bef) || (!ft_strcmp(l, "pa") && bef))
		fl = 22;
	return (fl);
}

/*
** do one command [line] on stacks [all.a] ans [all.b]
** if [free_line] - free line before return
** if [comm] is illegal - exit with cleaning [all]
*/

void		do_one_comm(t_stacks *all, char *l, char free_line, char f)
{
	if ((!ft_strcmp(l, "sa") || !ft_strcmp(l, "ss")) && (f = 1))
		swap_stack(&all->a);
	if ((!ft_strcmp(l, "sb") || !ft_strcmp(l, "ss")) && (f = 1))
		swap_stack(&all->b);
	if ((!ft_strcmp(l, "ra") || !ft_strcmp(l, "rr")) && (f = 1))
		rotate_stack(&all->a);
	if ((!ft_strcmp(l, "rb") || !ft_strcmp(l, "rr")) && (f = 1))
		rotate_stack(&all->b);
	if ((!ft_strcmp(l, "rra") || !ft_strcmp(l, "rrr")) && (f = 1))
		r_rotate_stack(&all->a);
	if ((!ft_strcmp(l, "rrb") || !ft_strcmp(l, "rrr")) && (f = 1))
		r_rotate_stack(&all->b);
	if (!ft_strcmp(l, "pa") && (f = 1))
		push_stack(&all->b, &all->a);
	else if (!ft_strcmp(l, "pb") && (f = 1))
		push_stack(&all->a, &all->b);
	if (free_line)
		free(l);
	if (!f)
		exit(clean(ERR_M, all));
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
