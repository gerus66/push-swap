/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_to_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 08:07:46 by mbartole          #+#    #+#             */
/*   Updated: 2019/02/27 11:02:57 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

static void	delete_ra(t_list **comm)
{
	t_list	*tmp;
	t_list	*del;

	if (!(*comm))
		return ;
	tmp = *comm;
	while (tmp->next && tmp->next->next)
		tmp = tmp->next;
	if (ft_strcmp(CCONT(tmp->next), "ra"))
		return ;
	del = tmp->next;
	tmp->next = NULL;
	ft_lstdelone(&del, NULL);
	delete_ra(comm);
}

static char	need_improve(t_list	*cur)
{
	if (cur && cur->next &&
			((!ft_strcmp(CCONT(cur), "ra") && !ft_strcmp(CCONT(cur->next), "rra")) ||
			 (!ft_strcmp(CCONT(cur), "rra") && !ft_strcmp(CCONT(cur->next), "ra")) ||
			 (!ft_strcmp(CCONT(cur), "rb") && !ft_strcmp(CCONT(cur->next), "rrb")) ||
			 (!ft_strcmp(CCONT(cur), "rrb") && !ft_strcmp(CCONT(cur->next), "rb"))))
		return (1);
	return (0);
}

static void	improve_comm(t_list **comm)
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
		improve_comm(comm);
	}
	cur = *comm;
	while (cur && cur->next && cur->next->next)
	{
		if (need_improve(cur->next))
		{
			tmp = cur->next;
			cur->next = cur->next->next;
			ft_lstdelone(&tmp, NULL);
			tmp = cur->next;
			cur->next = cur->next->next;
			ft_lstdelone(&tmp, NULL);
		}
		cur = cur->next;
	}
}
/*
void	do_push(t_list **a, t_list **b, t_list *comm)
{
	int c = 1;

	while (comm)
	{
		if (*b && (*b)->next)
		{
		if (!(ft_strcmp(CCONT(comm), "sa")) &&
				ICONT(*b) > ICONT((*b)->next) && c++)
			ft_memcpy(comm->cont, (void *)"ss", sizeof(char *));
		else if (!(ft_strcmp(CCONT(comm), "ra")) && 
					ICONT(*b) > last_elem(*b) && c++)
			ft_memcpy(comm->cont, (void *)"rr", sizeof(char *));
		else if (!(ft_strcmp(CCONT(comm), "rra")) && 
					ICONT(*b) > last_elem(*b) && c++)
			ft_memcpy(comm->cont, (void *)"rrr", sizeof(char *));
		}
		do_one_comm(a, b, comm);
		comm = comm->next;
	}
	printf("%d times\n", c - 1);
}
*/
t_list	*push_to_b(int *standing, t_list **a, t_list **b, int count)
{
	int		i;
	t_list	*comm;
	t_list	*cp;

	int counter = 0;

	comm = NULL;
	i = -1;
	while (++i < count)
	{
		if (standing[i] == 0)
			ft_lstadd_back(&comm, ft_lstnew("pb", 3));
		else if (standing[i] == -1)
		{
			ft_lstadd_back(&comm, ft_lstnew("rra", 4));
			ft_lstadd_back(&comm, ft_lstnew("sa", 3));
			ft_lstadd_back(&comm, ft_lstnew("ra", 3));
			ft_lstadd_back(&comm, ft_lstnew("ra", 3));
			counter++;
		}
		else
		{
			ft_lstadd_back(&comm, ft_lstnew("ra", 3));
			counter++;
		}
	}
	printf("--------TO B:   ---%d---\n", counter);
	print_comm(comm);
	delete_ra(&comm);
	print_comm(comm);
	improve_comm(&comm);
	print_comm(comm);
//	print_stacks(*a, *b);
	do_push(a, b, comm);
	print_comm(comm);
//	do_all_comm(a, b, comm);
//	print_stacks(*a, *b);
	return (comm);
}
