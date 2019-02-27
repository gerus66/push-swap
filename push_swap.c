/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 20:19:56 by mbartole          #+#    #+#             */
/*   Updated: 2019/02/27 12:59:05 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

int clean(char *msg)
{
	ft_putstr(msg);
	return (0);
}

void	lst_to_array(t_list *st, int *ar, int count)
{
	int	i;

	i = -1;
	while (st && ++i < count)
	{
		ar[i] = ICONT(st);
		st = st->next;
	}
}

static void init_razn(int *razn, int *sorted, t_list *in, int count)
{
	int	i;
	int	j;
	int	tmp;

	j = 0;
	while (in)
	{
		i = -1;
		while (++i < count)
			if (ICONT(in) == sorted[i])
				break ;
		tmp = j - i;
		if (tmp < -count / 2)
			tmp += count;
		else if (tmp > count / 2)
			tmp -= count;
		razn[j] = tmp;
		in = in->next;
		j++;
	}
}

static void	tree_to_lst(t_avltree *root, t_list **lst)
{
	if (root == NULL)
		return ;
	tree_to_lst(root->left, lst);
	ft_lstadd_back(lst, ft_lstnew((void *)&root->key, sizeof(int)));
	tree_to_lst(root->right, lst);
}

static int	*get_magic_sequence(t_list *in, char fl)
{
	t_avltree 	*tr;
	t_list		*tmpl;
	int			*sorted_ar;
	int			*razn;
	int			*standing;
	int			count;

	count = ft_lstlen(in);
	tr = NULL;
	tmpl = in;
	while (tmpl)
	{
		ft_tree_insert(&tr, ICONT(tmpl), NULL, 0);
		tmpl = tmpl->next;
	}
	tmpl = NULL;
	tree_to_lst(tr, &tmpl);
	//TODO free tree
	sorted_ar = (int *)ft_memalloc(sizeof(int) * count);
	lst_to_array(tmpl, sorted_ar, count);
	ft_lstdel(&tmpl, NULL);
	razn = (int *)ft_memalloc(sizeof(int) * count);
	init_razn(razn, sorted_ar, in, count);
	choose_sequence(count, in, &standing);
	int i = -1;
	while (++i < count)
		printf(" %d ", standing[i]);
//	choose_sequence(razn, &standing, count, fl);
	return (standing);
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

static t_list	*push_last(t_list **a, t_list **b)
{
	t_list	*comm;
	t_list	*cp;
	int		count;
	int		len;
	int		first;

	first = ICONT(*b);
	len = ft_lstlen(*a);
	comm = NULL;
	cp = *a;
	count = 0;
	while (!((ICONT(cp) > first && first > last_elem(cp)) ||
			(last_elem(cp) < first && ICONT(cp) < last_elem(cp)) ||
			(ICONT(cp) > first && ICONT(cp) < last_elem(cp))))
	{
		cp = cp->next;
		count++;
	}
	printf("LAST: %d\n", count);
	if (count < len / 2)
		while (count--)
			ft_lstadd_back(&comm, ft_lstnew("ra", 3));
	else
	{
		count = len - count;
		while (count--)
			ft_lstadd_back(&comm, ft_lstnew("rra", 4));
	}
	ft_lstadd_back(&comm, ft_lstnew("pa", 3));
	do_all_comm(a, b, comm);
	return (comm);
}

static t_list	*rot_all(t_list **a, t_list **b, int *seq, int count)
{
	t_list	*comm;
	t_list	*all_comm;
	t_list	*cp;
	t_list	*cp2;
	int		first;
	int		i;
	int		cccount;

//	printf("\nrot it all\n");
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
		first = ICONT(cp);
//		printf("|");
//		printf("first to push: %d\n", first);
		cp = *a;
		cccount = 0;
		while (!((ICONT(cp) > first && first > last_elem(cp)) ||
				(last_elem(cp) < first && ICONT(cp) < last_elem(cp)) ||
				(ICONT(cp) > first && ICONT(cp) < last_elem(cp))))
		{
			cccount++;
			cp = cp->next;
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
		//	cp = cp->next;
			}
		}
		else
		{
			cccount = ft_lstlen(*a) - cccount;
			while (cccount--)
				ft_lstadd_back(&comm, ft_lstnew("rra", 4));
		}
		ft_lstadd_back(&comm, ft_lstnew("pa", 3));
		cp = comm;
		while (cp)
		{
			if (!seq[i+1] )
			do_all_push(a, b, comm);
		}
//		do_all_comm(a, b, comm);
//		print_comm(comm);
//		print_stacks(*a, *b);
		add_comm(&all_comm, comm);
		i++;
	}
	if (!count)
		return (push_last(a, b));
//	print_comm(all_comm);
//	printf("rotated!\n\n");
	return (all_comm);
}

int	main(int argc, char **argv)
{
	t_list	*a;
	t_list	*b;
	t_list	*comm;
	int		len;
	int		*seq;

	if (argc < 2)
		return (clean("Error\n"));
	a = NULL;
	len = argv_to_list(&a, argv, argc - 1);
//	print_stacks(a, NULL);
	seq = get_magic_sequence(a, 1);
	b = NULL;
	comm = NULL;
	add_comm(&comm, push_to_b(seq, &a, &b, len));
//	print_stacks(a, b); //
//	print_comm(comm);
//	printf("in cycle:\n");
	while (b)
	{
	seq = get_magic_sequence(b, 0);
	add_comm(&comm, rot_all(&a, &b, seq, ft_lstlen(b) - 1));
	print_comm(comm);
//	print_stacks(a, b); //
	}

	return (0);
}
