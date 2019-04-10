/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 14:28:39 by mbartole          #+#    #+#             */
/*   Updated: 2019/04/10 05:18:14 by mbartole         ###   ########.fr       */
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

static t_list	*final_rotation(t_list **st)
{
	t_list	*comm;
	int		len;

	comm = NULL;
	len = ft_lstlen(*st);
	if (len - ICONT(*st) < len / 2)
		while (ICONT(*st) != 0)
			add_and_do(&comm, st, NULL, "ra");
	else
		while (ICONT(*st) != 0)
			add_and_do(&comm, st, NULL, "rra");
	return (comm);
}

int			main(int argc, char **argv)
{
	t_list	*a;
	t_list	*b;
	//	t_list	*cp;
	int		*standing;
	int		len;
	int		subseq;
	t_list	*comm;
//	t_list	*to_push;
	t_list	*new_comm;

//	comm = NULL;
	if (argc < 2)
		return (clean("Error\n"));
	a = NULL;
	b = NULL;
	len = argv_to_list(&a, argv, argc - 1, 1);
//	print_stack(a);
	choose_sequence(get_diff(a, 1, 0, ft_lstlen(a)), &standing, len, 1);
//	improve_seq(a, standing);
//	to_push = get_to_push(standing, a);
	comm = push_b(standing, &a, &b);
//	clever_push_b(comm, &a, &b, to_push);
//	printf("first push to B:   ");//
//	print_comm(comm);//
	while (ft_lstlen(b) > 5)
	{
//		printf("A: %d	B: %d\n", ft_lstlen(a), ft_lstlen(b));//
		new_comm = back_to_a(&a, &b);
//		printf("cycle:   ");//
//		print_comm(new_comm);//
		add_comm(&comm, new_comm);
		if (ft_lstlen(last(b)) < len)
			break ;
	}
	new_comm = last(b);
//	printf("INSERT (%d):   ", ft_lstlen(b));//
//	print_comm(new_comm);//
	do_all_comm(&a, &b, new_comm, 0);
	add_comm(&comm, new_comm);
//	print_stacks(a, b);
	new_comm = back_to_a_last(&a, &b);
//	printf("final push to A:   ");//
//	print_comm(new_comm);//
	add_comm(&comm, new_comm);
	new_comm = final_rotation(&a);
//	printf("final rotation:   ");//
//	print_comm(new_comm);//
	add_comm(&comm, new_comm);
//	printf("before improve:   ");//
//	print_comm(comm);
	improve_comm(&comm);
	improve_comm_dub(&comm);
//	printf("FINAL:   ");//
	print_comm(comm);
//	print_stack(a);//
	return (0);
}
