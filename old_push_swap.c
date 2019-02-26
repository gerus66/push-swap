/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 14:28:39 by mbartole          #+#    #+#             */
/*   Updated: 2019/02/26 00:41:36 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

#define ABS(x) ((x) < 0 ? -(x) : (x))

/*static int	get_rot_b(t_list *to_push, t_list *b)
{
	int rot;
	int	len;

//	print_stacks(to_push, b);
	len = ft_lstlen(b);
	if (len < 2 || !to_push)
		return (0);
	rot = 1;
	while (b && b->next)
	{
	//	printf("next to push: %d ", ICONT(to_push));
		if ((ICONT(b) > ICONT(to_push) && ICONT(to_push) > ICONT(b->next)) ||
			(ICONT(b) < ICONT(b->next) && ICONT(to_push) > ICONT(b->next)) ||
			(ICONT(b) < ICONT(b->next) && ICONT(to_push) < ICONT(b)))
			break ;
		b = b->next;
		rot++;
	}
	if (!(b->next))
		return (0);
	return (rot <= len / 2 ? rot : rot - len);
}*/

/*static void	clever_push_b(t_list *comm, t_list **a, t_list **b, t_list *to_push)
{
	int	rot_b;
	t_list	*tmp;
	t_list	*prev;

	prev = comm;
	while (comm)
	{
		rot_b = get_rot_b(to_push, *b);
	//	printf("rot_b----|%d|----\n", rot_b);
		if (rot_b > 0 && !ft_strcmp(CCONT(comm), "ra"))
		{
			ft_memcpy(comm->cont, (void *)"rr", sizeof(char *));
			rot_b--;
		}
		else if (rot_b < 0 && !ft_strcmp(CCONT(comm), "rra"))
		{
			ft_memcpy(comm->cont, (void *)"rrr", sizeof(char *));
			rot_b++;
		}
		if (!ft_strcmp(CCONT(comm), "pb"))
		{
			to_push = to_push->next;
			while (rot_b)
			{
				tmp = rot_b > 0 ? ft_lstnew("rb", 3) : ft_lstnew("rrb", 4);
				prev->next = tmp;
				tmp->next = comm;
				comm = tmp;
				rot_b = rot_b > 0 ? rot_b - 1 : rot_b + 1;
				do_one_comm(a, b, comm);
				prev = comm;
				comm = comm->next;
	//			printf("________eval_rot_b______%d\n", rot_b);
			}
		}
		do_one_comm(a, b, comm);
		prev = comm;
		comm = comm->next;
	}
}*/

static void	rot_to_comm(int rot_a, int rot_b, t_list *comm)
{
	int	i;

	if (rot_a > 0 && rot_b > 0)
	{
		while (rot_a && rot_b)
		{
			ft_lstadd_back(&comm, ft_lstnew("rr", 3));
			rot_a--;
			rot_b--;
		}
		i = rot_a ? rot_a : rot_b;
		while (i-- > 0)
			ft_lstadd_back(&comm, ft_lstnew(rot_a? "ra" : "rb", 3));
	}
	else if (rot_a < 0 && rot_b < 0)
	{
		while (rot_a && rot_b)
		{
			ft_lstadd_back(&comm, ft_lstnew("rrr", 4));
			rot_a++;
			rot_b++;
		}
		i = rot_a ? rot_a : rot_b;
		while (i++ < 0)
			ft_lstadd_back(&comm, ft_lstnew((rot_a ? "rra" : "rrb"), 4));
	}
	else
	{
		while (rot_a)
		{
			ft_lstadd_back(&comm, ft_lstnew((rot_a > 0 ? "ra" : "rra"), 3));
			rot_a = rot_a > 0 ? rot_a - 1 : rot_a + 1;
		}
		while (rot_b)
		{
			ft_lstadd_back(&comm, ft_lstnew((rot_b > 0 ? "rb" : "rrb"), 3));
			rot_b = rot_b > 0 ? rot_b - 1 : rot_b + 1;
		}
	}
}

static void	rotate_all(t_list **a, t_list **b, t_list *comm)
{
	t_list	*tmp;
	int		rot_a;
	int		rot_b;
	int		len;
	int		max;

	tmp = *a;
	rot_a = 0;
	while (tmp && tmp->next)
	{
		if (ICONT(tmp) > ICONT(tmp->next))
			break ;
		rot_a++;
		tmp = tmp->next;
	}
	max = ICONT(tmp);
	len = ft_lstlen(*a);
	rot_a = rot_a < len / 2 ? rot_a : rot_a - len;
	tmp = *b;
	rot_b = 0;
	while (tmp && tmp->next)
	{
		if (ICONT(tmp) < ICONT(tmp->next))
			break ;
		rot_b++;
		tmp = tmp->next;
	}
	rot_b++;
	if (max < ICONT(tmp->next))
		rot_a++;
	len = ft_lstlen(*b);
	if (rot_a > 0)
		if (len - rot_b < rot_b - rot_a)
			rot_b = rot_b - len;
	if (rot_a < 0)
		if (rot_b > len - rot_b + rot_a)
			rot_b = rot_b - len;
	rot_b = rot_b < len / 2 ? rot_b : rot_b - len;
	len = ft_lstlen(comm);
	rot_to_comm(rot_a, rot_b, comm);
	while (len--)
		comm = comm->next;
	do_all_comm(a, b, comm);
}

static void	push_a(t_list **a, t_list **b, t_list *comm)
{
	t_list	*tmp;

	if (ICONT(*b) > ICONT(*a))
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
}
/*
int			main(int argc, char **argv)
{
	t_list	*a;
	t_list	*aaa;
	t_list	*b;
	t_list	*razn;
	t_list	*to_push;
	int		*standing;
	int		len;
	//	int		i;
	t_list	*comm;

	comm = NULL;
	if (argc < 2)
		return (clean("Error\n"));
	a = NULL;
	b = NULL;
	razn = NULL;
	len = argc - 1;
	init_stacks(&aaa, NULL, &len, argv);
	len = argc - 1;
	init_stacks(&a, &razn, &len, argv);
	standing = choise_standing(razn, len);
	to_push = push_b(standing, &comm, len, a);
//	print_stacks(aaa, b);//
//	print_comm(comm);//
//	printf("=========================\n");
	improve_comm(&comm);
//	print_stacks(a, b);//
//	print_comm(comm);//
//	printf("=========================\n");
	clever_push_b(comm, &a, &b, to_push);
//	print_stacks(a, b);//
//	print_comm(comm);//
//	printf("=========================\n");
	rotate_all(&a, &b, comm);
//	print_stacks(a, b);//
//	print_comm(comm);//
//	printf("=========================\n");
	push_a(&a, &b, comm);
//	print_stacks(a, b);//
//	print_comm(comm);//
//	printf("=========================\n");
//		b = NULL;
//		comm_stacks(&aaa, &b, comm);
//		print_stacks(aaa, b);
	print_comm(comm);//
	return (0);
}*/
