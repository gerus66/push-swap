/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 14:28:39 by mbartole          #+#    #+#             */
/*   Updated: 2019/03/14 23:15:44 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

#define ABS(x) ((x) < 0 ? -(x) : (x))

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
}*/

static t_list	*split_on_two(t_list **a, t_list **b)
{
	t_list	*comm;
	t_list	*cp;
	int		len;
	int		i;

	comm = NULL;
	len = ft_lstlen(*a);
	cp = *a;
	i = -1;
	while (++i < len)
	{
		ft_lstadd_back(&comm, ft_lstnew((ICONT(cp) % 2 ? "pb" : "ra"), 3));
		cp = cp->next;
	}
	delete_tail(&comm, "ra");
	do_all_comm(a, b, comm, 0);
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

static void	argv_to_list(t_list **in, char **argv, int count)
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
//	return (ft_lstlen(*in));
}

int			main(int argc, char **argv)
{
	t_list	*a;
	t_list	*b;
//	int		*seq_a;
//	int		*seq_b;
//	int		len;
	t_list	*comm;
//	t_list	*to_push;
//	t_list	*to_stay;

//	comm = NULL;
	if (argc < 2)
		return (clean("Error\n"));
	a = NULL;
	b = NULL;
	argv_to_list(&a, argv, argc - 1);
	print_stacks(a, b);
//	choose_sequence(get_diff(a, 1), &seq_a, ft_lstlen(a), 1);
	comm = split_on_two(&a, &b);
//	printf("INPUT:\n");
	print_stacks(a, b);
	while (stacks_magic(&a, &b, &comm))
		;
//	to_push = get_to_push(standing, a);
//	push_b(standing, &a, &b, &comm);
//	printf("TO B:\n");
//	print_stacks(to_push, NULL);
//	clever_push_b(comm, &a, &b, to_push);
//	print_stacks(a, b);
//	print_comm(comm);
//	do_all_comm(&a, &b, comm);
//	while (ft_lstlen(b) > 3)
//	{
//		choose_sequence(get_diff(b, 1), &standing, ft_lstlen(b), 0);
//		add_comm(&comm, rot_all(&a, &b, standing, ft_lstlen(b) - 1));
//		print_comm(comm);
//		print_stacks(a, b);
//	}
//	add_comm(&comm, last(&b));
//	choose_sequence(get_diff(b, 1), &standing, ft_lstlen(b), 0);
//	add_comm(&comm, rot_all(&a, &b, standing, ft_lstlen(b) - 1));
//	push_a(&a, &b, comm);
//	printf("RESULT:\n");
//	print_stacks(a, b);//
	print_comm(comm);//
	return (0);
}
