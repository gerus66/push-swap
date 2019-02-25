/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 14:28:39 by mbartole          #+#    #+#             */
/*   Updated: 2019/02/25 20:05:44 by mbartole         ###   ########.fr       */
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

static void init_razn(t_list **razn, int *sorted, t_list *in, int count)
{
	int	i;
	int	j;
	int	tmp;

//	printf("count %d\n", count);
	j = 0;
	while (in)
	{
		i = -1;
		while (++i < count)
			if (ICONT(in) == sorted[i])
			{
				ft_memcpy(in->cont, (void *)&i, sizeof(int));
				break ;
			}
		tmp = j - i;
		if (tmp < -count / 2)
			tmp += count;
		else if (tmp > count / 2)
			tmp -= count;
		ft_lstadd_back(razn, ft_lstnew((void *)&tmp, sizeof(int)));
		in = in->next;
		j++;
	}
}

static void	init_stacks(t_list **in, t_list **razn, int *count, char **argv)
{
	t_avltree *tr;
	t_list	*tmpl;
	int		tmp;
	int		i;
	int		*sorted_ar;
	char	**ar;

	tr = NULL;
	i = 0;
	while (++i <= *count)
	{
		ar = ft_strsplit(argv[i], ' ');
		while (*ar)
		{
			tmp = atoi_check(*ar);
			ft_lstadd_back(in, ft_lstnew((void *)&tmp, sizeof(int)));
			ft_tree_insert(&tr, atoi_check(*ar), NULL, 0);
			ar++;
		}
	}
	tmpl = NULL;
	tree_to_lst(tr, &tmpl);
	//TODO free tree
	*count = ft_lstlen(*in);
	sorted_ar = (int *)ft_memalloc(sizeof(int) * *count);
	lst_to_array(tmpl, sorted_ar, *count);
	ft_lstdel(&tmpl, NULL);
	if (razn)
		init_razn(razn, sorted_ar, *in, *count);
}

static int	*positive_seq(int *razn, int start, int count)
{
	int	*standing;
	int	i;
	int	last;
	int	prev;
	int	fl;

	if (!(standing = (int *)ft_memalloc(sizeof(int) * count)))
		return (NULL);
	standing[start] = 1;
	last = razn[start];
	prev = count;//
	i = start;//
	fl = 0;
	while (++i < count)
	{
		if (razn[i] <= last && razn[i] >= 0 
				&& razn[i] >= razn[start] - start - (count - i - 1))//
		{
			fl++;
			standing[i] = 1;
			prev = last;
			last = razn[i];
		}
		else if (razn[i] > last && razn[i] <= prev)
		{
			if (fl == 0)
			{
				start = i;
				fl++;
			}
			prev = razn[i];
			standing[i] = -1;
			last++;//
		}
		else
		{
			last++;
			prev++;
		}
	}
	return (standing);
}

static int	*negative_seq(int *razn, int start, int count)
{
	int	*standing;
	int	i;
	int	last;
	int	prev;
	int	fl;

	if (!(standing = (int *)ft_memalloc(sizeof(int) * count)))
		return (NULL);
	standing[start] = 1;
	last = razn[start];
	prev = 0;
	i = start;//
	fl = 0;
	while (++i < count)
	{
		if (razn[i] <= last && 
				razn[i] >= razn[start] - start - (count - i - 1))
		{
			fl++;
			standing[i] = 1;
			prev = last;
			last = razn[i];
		}
		else if (razn[i] > last && razn[i] <= prev)
		{
			if (fl == 0)
			{
				start = i;
				fl++;
			}
			prev = razn[i];
			standing[i] = -1;
			last++;//
		}
		else
		{
			last++;
			prev++;
		}
	}
	return (standing);
}

static int	stand_count(int *ar, int count)
{
	int	stand;
	int	i;

	stand = 0;
	i = -1;
	while (++i < count)
		if (ar[i])
			stand++;
	return (stand);
}

static void add_array(int *ar, int *add, int count)
{
	int	i = -1;

	while (++i < count)
		if (add[i])
			ar[i] = 1;
}

static int	*choise_standing(t_list *razn, int count)
{
	int	razn_ar[count];
	int	*standing;
	int	*standing_tmp;
	int	i;
	int stand;
	int	stand_tmp;
	int	fill[count];

	i = -1;
	while (++i < count)
		fill[i] = 0;
	lst_to_array(razn, razn_ar, count);
	standing = NULL;
	stand = 0;
	i = -1;
	while (++i < count - stand)
		if (!fill[i])
		{
			standing_tmp = (razn_ar[i] <= 0) ? negative_seq(razn_ar, i, count) :
				positive_seq(razn_ar, i, count);
			stand_tmp = stand_count(standing_tmp, count);
			add_array(fill, standing_tmp, count);
			//	printf("i = %d, stand_tmp = %d\n", i, stand_tmp);
			if (stand_tmp > stand)
			{
				free(standing);
				standing = standing_tmp;
				stand = stand_tmp;
			}
		}
	/*	i = -1;
		while (++i < count)
		printf("/%d/", standing[i]);*/
//	printf("\nstand = %d\n", stand);
	return (standing);
}

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
}

static t_list	*push_b(int *standing, t_list **comm, int count, t_list *a)
{
	int	i;
	t_list	*to_push;

	to_push = NULL;
	i = -1;
	while (++i < count)
	{
		if (standing[i] == 0)
		{
			ft_lstadd_back(comm, ft_lstnew("pb", 3));
			ft_lstadd_back(&to_push,ft_lstnew(a->cont, sizeof(int)));
		}
		else if (standing[i] == -1)
		{
			ft_lstadd_back(comm, ft_lstnew("rra", 4));
			ft_lstadd_back(comm, ft_lstnew("sa", 3));
			ft_lstadd_back(comm, ft_lstnew("ra", 3));
			ft_lstadd_back(comm, ft_lstnew("ra", 3));
		}
		else
			ft_lstadd_back(comm, ft_lstnew("ra", 3));
		a = a->next;
	}
	delete_ra(comm);
	return (to_push);
}

static void	clever_push_b(t_list *comm, t_list **a, t_list **b, t_list *to_push)
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
				one_comm_stacks(a, b, comm);
				prev = comm;
				comm = comm->next;
	//			printf("________eval_rot_b______%d\n", rot_b);
			}
		}
		one_comm_stacks(a, b, comm);
		prev = comm;
		comm = comm->next;
	}
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
	rot_to_comm(rot_a, rot_b, comm);
	while (len--)
		comm = comm->next;
	comm_stacks(a, b, comm);
}

static void	push_a(t_list **a, t_list **b, t_list *comm)
{
	t_list	*tmp;

	if (ICONT(*b) > ICONT(*a))
	{
		tmp = ft_lstnew("pa", 3);
		ft_lstadd_back(&comm, tmp);
		one_comm_stacks(a, b, tmp);
	}
	while (*b)
	{
		if (ICONT(*b) == ICONT(*a) - 1)
			tmp = ft_lstnew("pa", 3);
		else
			tmp = ft_lstnew("rra", 4);
		ft_lstadd_back(&comm, tmp);
		one_comm_stacks(a, b, tmp);
	}
//	printf("/// %d ///\n", ICONT(*a));
	while (ICONT(*a) != 0)
	{
		tmp = ft_lstnew("rra", 4);
		ft_lstadd_back(&comm, tmp);
		one_comm_stacks(a, b, tmp);
	}
}

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
}
