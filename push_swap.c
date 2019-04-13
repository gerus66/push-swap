/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 14:28:39 by mbartole          #+#    #+#             */
/*   Updated: 2019/04/13 17:11:13 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

static char	need_improve_a(t_list	*cur)
{
	if (cur && cur->next && cur->next->next &&
			(!ft_strcmp(CCONT(cur), "ra") &&
			  !ft_strcmp(CCONT(cur->next), "pa") &&
			  !ft_strcmp(CCONT(cur->next->next), "rra")))
		return (1);
	return (0);
}

static char	need_improve_b(t_list	*cur)
{
	if (cur && cur->next && cur->next->next &&
			(!ft_strcmp(CCONT(cur), "rb") &&
			  !ft_strcmp(CCONT(cur->next), "pb") &&
			  !ft_strcmp(CCONT(cur->next->next), "rrb")))
		return (1);
	return (0);
}

static void	improve_comm(t_list **comm)
{
	t_list	*tmp;
	t_list	*cur;

	cur = *comm;
	while (cur && cur->next && cur->next->next && cur->next->next->next)
	{
		if (need_improve_a(cur->next))
		{
			tmp = cur->next;
			cur->next = cur->next->next;
			ft_lstdelone(&tmp, NULL);
			cur = cur->next->next;
			ft_memcpy(cur->cont, (void *)"sa", sizeof(char *));
		}
		cur = cur->next;
	}
	cur = *comm;
	while (cur && cur->next && cur->next->next && cur->next->next->next)
	{
		if (need_improve_b(cur->next))
		{
			tmp = cur->next;
			cur->next = cur->next->next;
			ft_lstdelone(&tmp, NULL);
			cur = cur->next->next;
			ft_memcpy(cur->cont, (void *)"sb", sizeof(char *));
		}
		cur = cur->next;
	}
}

/*
 ** rotate sorted stack to the start [ < N / 2]
 */

static t_list	*final_rotation(t_stacks *all)
{
	t_list	*comm;
	int		len;

	comm = NULL;
	len = ft_lstlen(all->a);
	if (len - ICONT(all->a) < len / 2)
		while (ICONT(all->a) != 0)
			add_and_do(all, &comm, "ra");
	else
		while (ICONT(all->a) != 0)
			add_and_do(all, &comm, "rra");
	return (comm);
}

int			main(int argc, char **argv)
{
	int		*sorted;
	t_stacks all;
	t_list	*new_comm;

	if (argc < 2)
		return (0);
	init_all(&all, argv, argc - 1, 1);
	if (all.len_a == 1)
		return (clean("", &all));
	if (all.len_a == 2)
	{
		if (ICONT(all.a) > ICONT(all.a->next))
			return (clean("sa\n", &all));
		return (clean("", &all));
	}
	if (!(sorted = (int *)malloc(all.len_a * sizeof(int))))
		return (clean("ERM_M", &all));
	get_diff(all.a, sorted, 1, 0);
	choose_sequence(sorted, all.len_a);
	push_b(sorted, &all);
	free(sorted);
	new_comm = NULL;
	while (ft_lstlen(all.b) > 5)
	{
		back_to_a(&all);
		if (ft_lstlen((new_comm = last(&all, ft_lstlen(all.b)))) < all.len_a)
			break ;
	}
	if (!new_comm)
		new_comm = last(&all, ft_lstlen(all.b));
	do_all_comm(&all, new_comm);
	ft_lstadd_back(&all.comm, new_comm);
	last_push(&all);
//	printf("final push to A:   ");//
//	print_comm(new_comm);//
//	ft_lstadd_back(&all.comm, new_comm);
	new_comm = final_rotation(&all);
//	printf("final rotation:   ");//
//	print_comm(new_comm);//
	ft_lstadd_back(&all.comm, new_comm);
//	printf("before improve:   ");//
//	print_comm(comm);
	improve_comm(&all.comm);
	improve_comm_dub(&all.comm);
//	printf("FINAL:   ");//
	print_comm(all.comm);
//	print_stack(all.a);//
	return (clean("", &all));
}
