/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_to_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 08:07:46 by mbartole          #+#    #+#             */
/*   Updated: 2019/04/13 16:43:36 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

static char		need_improve(t_list *cur)
{
	if (cur && cur->next && (
		(!ft_strcmp(CCONT(cur), "ra") && !ft_strcmp(CCONT(cur->next), "rra")) ||
		(!ft_strcmp(CCONT(cur), "rra") && !ft_strcmp(CCONT(cur->next), "ra")) ||
		(!ft_strcmp(CCONT(cur), "rb") && !ft_strcmp(CCONT(cur->next), "rrb")) ||
		(!ft_strcmp(CCONT(cur), "rrb") && !ft_strcmp(CCONT(cur->next), "rb"))))
		return (1);
	return (0);
}

static void		del_next(t_list *cur)
{
	t_list	*tmp;

	tmp = cur->next;
	cur->next = cur->next->next;
	ft_lstdelone(&tmp, NULL);
}

void			improve_comm_dub(t_list **comm)
{
	t_list	*tmp;
	t_list	*cur;

	if (need_improve(*comm))
	{
		tmp = *comm;
		*comm = (*comm)->next;
		ft_lstdelone(&tmp, NULL);
		tmp = *comm;
		*comm = (*comm)->next;
		ft_lstdelone(&tmp, NULL);
		improve_comm_dub(comm);
	}
	cur = *comm;
	while (cur && cur->next && cur->next->next)
	{
		if (need_improve(cur->next))
		{
			del_next(cur);
			del_next(cur);
		}
		cur = cur->next;
	}
}

static t_list	*add_chaos(t_list *comm)
{
	t_list	*cp;

	cp = comm;
	while (comm)
	{
		if (!(ft_strcmp(CCONT(comm), "sa")))
			ft_memcpy(comm->cont, (void *)"ss", sizeof(char *));
		else if (!(ft_strcmp(CCONT(comm), "ra")))
			ft_memcpy(comm->cont, (void *)"rr", sizeof(char *));
		else if (!(ft_strcmp(CCONT(comm), "rra")))
			ft_memcpy(comm->cont, (void *)"rrr", sizeof(char *));
		comm = comm->next;
	}
	return (cp);
}

void			push_b(int *standing, t_stacks *all)
{
	int		i;
	int		count;
	t_list	*tmp;

	i = -1;
	tmp = all->a;
	count = all->len_a;
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
		tmp = tmp->next;
	}
	cut_tail(&all->comm, "ra");
	improve_comm_dub(&all->comm);
	do_all_comm(all, add_chaos(all->comm));
}
