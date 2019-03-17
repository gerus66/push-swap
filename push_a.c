/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_a.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 15:50:11 by mbartole          #+#    #+#             */
/*   Updated: 2019/03/17 22:43:10 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

t_list	*get_to_push(int *seq, t_list *st)
{
	int		i;
	int		count;
	t_list	*to_push;

	count = ft_lstlen(st);
	to_push = NULL;
	i = -1;
	while (++i < count)
	{
		if (seq[i] == 0)
			ft_lstadd_back(&to_push,ft_lstnew(st->cont, sizeof(int)));
		st = st->next;
	}
	return (to_push);
}
/*
t_list	*adjust_stacks(t_list *a, t_list *b, t_list *to_push)
{
	int lena;
	int	lenb;
	int	rot;
	t_list	prev;

	lena = ft_lstlen(a);
	lenb = ft_lstlen(b);
	rot = 0;
	while (ICONT(b) != ICONT(to_push))
	{
		b = b->next;
		rot++;
	}
	prev = last_elem(a);
	while()
}*/

t_list	*rot_all(t_list **a, t_list **b, int *seq, int count)
{
	t_list	*comm;
	t_list	*all_comm;
	t_list	*cp;
	t_list	*cp2;
	t_list	*cp3;
	int		to_push;
	int		i;
	int		cccount;
	int		prev;

	i = 0;
	all_comm = NULL;
	count++;
	prev = 0;
	while (i < count)
	{
		cp = *b;
		comm = NULL;
		while (!seq[i] && i < count)
		{
	//	print_stacks(*a, *b);
	/*			if (seq[i + 1] == 0 && cp->next && prev > ICONT(cp->next))
				{
				ft_lstadd_back(&comm, ft_lstnew("sb", 3));
				printf("S %d <-> %d\n", prev, ICONT(cp->next));
			//	print_comm(comm);
				}
				else if (cp->next)
				prev = ICONT(cp->next);*/
			cp = cp->next;
			ft_lstadd_back(&comm, ft_lstnew("rb", 3));
			i++;
		}
		if (i == count)
			break ;
		to_push = ICONT(cp);
		cp3 = *a;
		cccount = 0;
		prev = last_elem(cp3);
		while (!((to_push < ICONT(cp3) && to_push > prev) ||
					(to_push > ICONT(cp3) && to_push > prev && prev > ICONT(cp3)) ||
					(to_push < ICONT(cp3) && ICONT(cp3) < prev)))
		{
			cccount++;
			prev = ICONT(cp3);
			cp3 = cp3->next;
		}
		if (cccount < ft_lstlen(*a) / 2)
		{
			cp2 = comm;
			while (cccount--)
			{
				if (cp2 && (!ft_strcmp(CCONT(cp2), "rb")))
				{
					ft_memcpy(cp2->cont, (void *)"rr", sizeof(char *));
					cp2 = cp2->next;
				}
				else
					ft_lstadd_back(&comm, ft_lstnew("ra", 3));
			}
		}
		else
		{
			cccount = ft_lstlen(*a) - cccount;
			while (cccount--)
				ft_lstadd_back(&comm, ft_lstnew("rra", 4));
		}
		ft_lstadd_back(&comm, ft_lstnew("pa", 3));
		do_all_comm(a, b, comm, 0);
		add_comm(&all_comm, comm);
		i++;
//		print_stacks(*a, *b);
	}
	return (all_comm);
}
/*
void	push_a(t_list **a, t_list **b, t_list *comm)
{
	t_list	*tmp;

	print_comm(comm);
	printf("start push to A\n");
	if (*b && ICONT(*b) > ICONT(*a))
	{
		tmp = ft_lstnew("pa", 3);
		ft_lstadd_back(&comm, tmp);
		do_one_comm(a, b, tmp);
	}
	while (*b)
	{
		if (ICONT(*b) == ICONT(*a) - 1)
			tmp = ft_lstnew("pa", 3);
		else
			tmp = ft_lstnew("rra", 4);
		ft_lstadd_back(&comm, tmp);
		do_one_comm(a, b, tmp);
	}
	while (ICONT(*a) != 0)
	{
		tmp = ft_lstnew("rra", 4);
		ft_lstadd_back(&comm, tmp);
		do_one_comm(a, b, tmp);
	}
}*/
