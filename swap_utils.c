/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 08:24:33 by mbartole          #+#    #+#             */
/*   Updated: 2019/02/27 11:15:37 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

void	print_comm(t_list *comm)
{
	t_list	*tmp;

	tmp = comm;
	while (comm)
	{
//		printf("%s ", (char *)comm->cont);
		comm = comm->next;
	}
	printf("count: %d\n", ft_lstlen(tmp));
}

void		print_stacks(t_list *a, t_list *b)
{
	while (a || b)
	{
		printf("%6d %6d\n", (a ? ICONT(a) : 0),
				(b ? ICONT(b) : 0));
		if (a)
			a = a->next;
		if (b)
			b = b->next;
	}
	printf("%6c %6c\n", '_', '_');
	printf("%6c %6c\n\n", 'a', 'b');
}

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

void	do_all_push(t_list **a, t_list **b, t_list *comm)
{
	while (comm)
	{
		do_push(a, b, comm);
		comm = comm->next;
	}
}
