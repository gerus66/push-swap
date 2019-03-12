/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 14:28:39 by mbartole          #+#    #+#             */
/*   Updated: 2019/03/12 20:21:29 by mbartole         ###   ########.fr       */
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
		printf("%s\n", (char *)comm->cont);
		comm = comm->next;
	}
//	printf("\ncount: %d\n", ft_lstlen(tmp));
}
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
i				*comm = (*comm)->next;
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

static void	push_a(t_list **a, t_list **b, t_list *comm)
{
	t_list	*tmp;

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
//		printf("/// %d ///\n", ICONT(*a));
	while (ICONT(*a) != 0)
	{
		tmp = ft_lstnew("rra", 4);
		ft_lstadd_back(&comm, tmp);
		do_one_comm(a, b, tmp);
	}
}

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
	int		prev;

//	printf("A: %d, B: %d\n", ft_lstlen(*a), ft_lstlen(*b));
	i = 0;
	all_comm = NULL;
	count++;
	while (i < count)
	{
		cp = *b;
		comm = NULL;
//		prev = ICONT(cp);
		while (!seq[i] && i < count)
		{
//			if (seq[i + 1] == 0 && cp->next && prev > ICONT(cp->next))
//			{
//				ft_lstadd_back(&comm, ft_lstnew("sb", 3));
//				printf("S %d <-> %d\n", prev, ICONT(cp->next));
	//			print_comm(comm);
//			}
//			else if (cp->next)
//				prev = ICONT(cp->next);
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
//		printf("|");
		do_all_comm(a, b, comm, 0);
	//	print_stacks(*a, *b);
	//	print_comm(comm);
		add_comm(&all_comm, comm);
	//	print_comm(all_comm);
		i++;
	}
//	print_stacks(*a, *b);
//	print_comm(all_comm);
	return (all_comm);
}

static t_list	*last(t_list **b)
{
	t_list	*comm;
	int		len;

	comm = NULL;
	len = ft_lstlen(*b);
	if (len == 0 || len == 1)
		return (NULL);
	if (len == 2 && ICONT(*b) > ICONT((*b)->next))
	{
		ft_lstadd_back(&comm, ft_lstnew("sb", 3));
		do_one_comm(NULL, b, ft_lstnew("sb", 3));
		return (comm);
	}
	if (len == 2)
		return (NULL);
	if (ICONT(*b) < ICONT((*b)->next) && ICONT(*b) < ICONT((*b)->next->next) && 
			ICONT((*b)->next) > ICONT((*b)->next->next))
	{
		ft_lstadd_back(&comm, ft_lstnew("rrb", 4));
		do_one_comm(NULL, b, ft_lstnew("rrb", 4));
	}
	else if (ICONT(*b) > ICONT((*b)->next) && ICONT(*b) > ICONT((*b)->next->next) && 
			ICONT((*b)->next) > ICONT((*b)->next->next))
	{
		ft_lstadd_back(&comm, ft_lstnew("rb", 3));
		do_one_comm(NULL, b, ft_lstnew("rb", 3));
	}
	if (ICONT(*b) > ICONT((*b)->next) && ICONT(*b) < ICONT((*b)->next->next))
	{
		ft_lstadd_back(&comm, ft_lstnew("sb", 3));
		do_one_comm(NULL, b, ft_lstnew("sb", 3));
	}
	return (comm);
}

static void	simplify(t_list *in)
{
	int	*sorted;
	int	i;
	int	count;

	count = ft_lstlen(in);
	sorted = get_diff(in, 0);
	while (in)
	{
		i = -1;
		while (++i < count)
			if (ICONT(in) == sorted[i])
			{
				ft_memcpy(in->cont, (void *)&i, sizeof(int));
				break ;
			}
		in = in->next;
	}
}

static int	argv_to_list(t_list **in, char **argv, int count)
{
	int		i;
	char	**ar;
	int		tmp;

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
	simplify(*in);
	return (ft_lstlen(*in));
}

int			main(int argc, char **argv)
{
	t_list	*a;
	t_list	*b;
	int		*standing;
	int		len;
	t_list	*comm;
	t_list	*to_push;

	comm = NULL;
	if (argc < 2)
		return (clean("Error\n"));
	a = NULL;
	b = NULL;
	len = argv_to_list(&a, argv, argc - 1);
//	printf("INPUT:\n");
//	print_stacks(a, b);
	choose_sequence(get_diff(a, 1), &standing, len, 1);
	to_push = push_b(standing, &a, &b, &comm);
//	printf("TO B:\n");
//	print_stacks(to_push, NULL);
	clever_push_b(comm, &a, &b, to_push);
//	print_stacks(a, b);
//	print_comm(comm);
//	do_all_comm(&a, &b, comm);
	while (ft_lstlen(b) > 3)
	{
		choose_sequence(get_diff(b, 1), &standing, ft_lstlen(b), 0);
		add_comm(&comm, rot_all(&a, &b, standing, ft_lstlen(b) - 1));
//		print_stacks(a, b);
	}
	add_comm(&comm, last(&b));
	push_a(&a, &b, comm);
//	printf("RESULT:\n");
//	print_stacks(a, b);//
	print_comm(comm);//
	return (0);
}
