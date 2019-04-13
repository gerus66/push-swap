/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 17:11:13 by mbartole          #+#    #+#             */
/*   Updated: 2019/04/13 13:55:24 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

/*
** do one command [line] on stacks [all.a] ans [all.b]
** if [free_line] - free line before return
** if [comm] is illegal - exit with cleaning [all]
*/

void	do_one_comm(t_stacks *all, char *line, char free_line)
{
	char	fl;

	fl = 0;
	if ((!ft_strcmp(line, "sa") || !ft_strcmp(line, "ss")) && (fl = 1))
		swap_stack(&all->a);
	if ((!ft_strcmp(line, "sb") || !ft_strcmp(line, "ss")) && (fl = 1))
		swap_stack(&all->b);
	if ((!ft_strcmp(line, "ra") || !ft_strcmp(line, "rr")) && (fl = 1))
		rotate_stack(&all->a);
	if ((!ft_strcmp(line, "rb") || !ft_strcmp(line, "rr")) && (fl = 1))
		rotate_stack(&all->b);
	if ((!ft_strcmp(line, "rra") || !ft_strcmp(line, "rrr")) && (fl = 1))
		r_rotate_stack(&all->a);
	if ((!ft_strcmp(line, "rrb") || !ft_strcmp(line, "rrr")) && (fl = 1))
		r_rotate_stack(&all->b);
	if (!ft_strcmp(line, "pa") && (fl = 1))
		push_stack(&all->b, &all->a);
	else if (!ft_strcmp(line, "pb") && (fl = 1))
		push_stack(&all->a, &all->b);
	if (free_line)
		free(line);
	if (!fl)
		exit(clean(ERR_M, all));
}

/*
** just cycle for do_one_comm
*/

void	do_all_comm(t_stacks *all, t_list *comm)
{
	while (comm)
	{
		do_one_comm(all, CCONT(comm), 0);
		comm = comm->next;
	}
}

/*
** add [name] command to [comm] list
** if smth wrong, exit with clean
*/

void	add_comm(t_stacks *all, t_list **comm, char *name)
{
	t_list	*tmp;

	if (!(tmp = ft_lstnew(name, sizeof(char) * (ft_strlen(name) + 1))))
		exit(clean(ERM_M, all));
	ft_lstadd_back(comm, tmp);
}

/*
** do one command [name] and add it to list [comm]
*/

void	add_and_do(t_stacks *all, t_list **comm, char *name)
{
	add_comm(all, comm, name);
	do_one_comm(all, name, 0);
}
