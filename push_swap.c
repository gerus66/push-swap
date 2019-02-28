/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 14:28:39 by mbartole          #+#    #+#             */
/*   Updated: 2019/03/01 02:34:37 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

#define ABS(x) ((x) < 0 ? -(x) : (x))

static void	print_comm(t_list *comm)
{
	t_list	*tmp;

	tmp = comm;
	while (comm)
	{
	//	printf("%s\n", (char *)comm->cont);
		comm = comm->next;
	}
	printf("\ncount: %d\n", ft_lstlen(tmp));
}
/*
static int	get_rot_b(t_list *to_push, t_list *b)
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
/*
static int	return_to_a(t_list **a, t_list **b, t_list *to_stand, t_list **comm, t_list **prev, int count)
{
	t_list	*tmp;

	if (!(*b) || !to_stand)
		return(0);
	tmp = to_stand;
	while (tmp->next)
		tmp = tmp->next;
	printf("\n");
	print_stacks(to_stand, NULL);
	print_stacks(*a, *b);
	printf(" try to return %d between %d and %d ", ICONT(*b), ICONT(tmp), ICONT(to_stand));
	if ((ICONT(*b) < ICONT(to_stand) && ICONT(*b) > ICONT(tmp)) ||
			(ICONT(to_stand) < ICONT(tmp) &&
			 ICONT(*b) > ICONT(to_stand) && ICONT(*b) < ICONT(tmp)))
	{
		printf(" - yes \n");
		//		print_stacks(*a, *b);
		//		print_comm(*comm);
		tmp = ft_lstnew("pa", 3);
		(*prev)->next = tmp;
		tmp->next = *comm;
		*comm = tmp;
		one_comm_stacks(a, b, *comm);
		*prev = *comm;
		*comm = (*comm)->next;
		count++;

		if (!(return_to_a(a, b, *a, comm, prev, count)))
		{
			while (count--)
			{
				tmp = ft_lstnew("ra", 3);
				(*prev)->next = tmp;
				tmp->next = *comm;
				*comm = tmp;
				one_comm_stacks(a, b, *comm);
				*prev = *comm;
				*comm = (*comm)->next;
			}
			//		print_stacks(*a, *b);
			//		print_comm(*comm);
			return (1);
		}
		//		printf("get   a: %d   b: %d   comm: %s \n",
		//				ICONT(*a), ICONT(*b), CCONT(*comm));
	}
	printf(" - no \n");
	return (0);
}*/
/*
static t_list	*lst_copy(t_list *lst)
{
	t_list	*new;

	new = NULL;
	while (lst)
	{
		ft_lstadd_back(&new, ft_lstnew(lst->cont, sizeof(int)));
		lst = lst->next;
	}
	return (new);
}*/
/*
static void	clever_push_b(t_list *comm, t_list **a, t_list **b, t_list *to_push)
{
	int	rot_b;
	t_list	*tmp;
	t_list	*prev;

	prev = comm;
	while (comm)
	{
		rot_b = get_rot_b(to_push, *b);
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
				one_comm_stacks(a, b, comm);
				prev = comm;
				comm = comm->next;
			}
		}
		one_comm_stacks(a, b, comm);
		prev = comm;
		comm = comm->next;
	}
}*/
/*
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
		//		printf("rot a: %d rot b: %d\n", rot_a, rot_b);
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
}*/
/*
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
	//	printf("rot a: %d rot b: %d\n", rot_a, rot_b);
	len = ft_lstlen(*b);
	if (rot_a > 0)
		if (len - rot_b < rot_b - rot_a)
			rot_b = rot_b - len;
	if (rot_a < 0)
		if (rot_b > len - rot_b + rot_a)
			rot_b = rot_b - len;
	rot_b = rot_b < len / 2 ? rot_b : rot_b - len;
	//	printf("rot a: %d rot b: %d\n", rot_a, rot_b);
	len = ft_lstlen(comm);
	printf("len of comm: %d\n", len);
	rot_to_comm(rot_a, rot_b, comm);
	printf("len of comm: %d\n", ft_lstlen(comm));
	while (len--)
		comm = comm->next;
	do_all_comm(a, b, comm);
}*/
/*
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
	//	printf("/// %d ///\n", ICONT(*a));
	while (ICONT(*a) != 0)
	{
		tmp = ft_lstnew("rra", 4);
		ft_lstadd_back(&comm, tmp);
		do_one_comm(a, b, tmp);
	}
}*/

static void		add_comm(t_list **comm, t_list *add)
{
	t_list	*tmp;

	if (!(*comm))
		*comm = add;
	else
	{
		tmp = *comm;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = add;
	}
}

static int		last_elem(t_list *stack)
{
	while (stack->next)
		stack = stack->next;
	return (ICONT(stack));
}

static t_list	*rot_all(t_list **a, t_list **b, int *seq, int count)
{
	t_list	*comm;
	t_list	*all_comm;
	t_list	*cp;
	t_list	*cp2;
	t_list	*cp3;
	int		to_push;
	int		i;
	int		cccount;

//	i = -1;
//	while (++i <= count)
//		printf(" %d", seq[i]);
//	printf("\n");
	i = 0;
	all_comm = NULL;
	while (i < count)
	{
		cp = *b;
		comm = NULL;
		while (!seq[i] && i < count)
		{
			cp = cp->next;
			ft_lstadd_back(&comm, ft_lstnew("rb", 3));
			i++;
		}
		if (i == count)
			break ;
		to_push = ICONT(cp);
//		printf("|");
//		printf("first to push: %d\n", to_push);
		cp3 = *a;
		cccount = 0;
		int	prev = last_elem(cp3);
		while (!((to_push < ICONT(cp3) && to_push > prev) ||
					(to_push > ICONT(cp3) && to_push > prev && prev > ICONT(cp3)) ||
					(to_push < ICONT(cp3) && ICONT(cp3) < prev)))
		{
//		printf("ping!\n");
			cccount++;
			prev = ICONT(cp3);
			cp3 = cp3->next;
		}
		if (cccount < ft_lstlen(*a) / 2)
		{
			cp2 = comm;
			while (cccount--)
			{
				if (cp2)
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
		do_all_comm(a, b, comm);
//		print_stacks(*a, *b);
		add_comm(&all_comm, comm);
		i++;
	//	sleep(1);
	}
//	if (!count)
//		return (push_last(a, b));
//	print_comm(all_comm);
	return (all_comm);
}

static int	argv_to_list(t_list **in, char **argv, int count)
{
	int		i;
	char	**ar;
	int		tmp;
	int		*sorted;
	t_list	*cp;

	i = 0;
	while (++i <= count)
	{
		ar = ft_strsplit(argv[i], ' ');
		while (*ar)
		{
			tmp = atoi_check(*ar);
			ft_lstadd_back(in, ft_lstnew((void *)&tmp, sizeof(int)));
			ar++;
		}
	}
	tmp = ft_lstlen(*in);
	sorted = get_diff(*in, 0);
	cp = *in;
	while (cp)
	{
		i = -1;
		while (++i < tmp)
			if (ICONT(cp) == sorted[i])
			{
				ft_memcpy(cp->cont, (void *)&i, sizeof(int));
				break ;
			}
		cp = cp->next;
	}
	return (ft_lstlen(*in));
}

int			main(int argc, char **argv)
{
	t_list	*a;
	t_list	*b;
	int		*standing;
	int		len;
	t_list	*comm;

	comm = NULL;
	if (argc < 2)
		return (clean("Error\n"));
	a = NULL;
	b = NULL;
	len = argv_to_list(&a, argv, argc - 1);
	print_stacks(a, b);
	choose_sequence(get_diff(a, 1), &standing, len, 0);
	push_b(standing, a, &comm, len);
	do_all_comm(&a, &b, comm);
	while (ft_lstlen(b) > 3)
	{
		choose_sequence(get_diff(b, 1), &standing, ft_lstlen(b), 0);
		add_comm(&comm, rot_all(&a, &b, standing, ft_lstlen(b) - 1));
	}
	print_stacks(a, b);//
	print_comm(comm);//
	return (0);
}
