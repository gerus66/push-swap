/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 14:28:39 by mbartole          #+#    #+#             */
/*   Updated: 2019/02/11 23:38:20 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

#define ABS(x) ((x) < 0 ? -(x) : (x))

static void init_razn(t_list **razn, int *sorted, t_list *in, int count)
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

static void	init_stacks(t_list **in, t_list **razn, int count, char **argv)
{
	t_avltree *tr;
	t_list	*tmpl;
	int		tmp;
	int		i;
	int		sorted_ar[count];
	
	tr = NULL;
	i = count + 1;
	while (--i > 0)
	{
		tmp = atoi_check(argv[i]);
		ft_lstadd(in, ft_lstnew((void *)&tmp, sizeof(int)));
		ft_tree_insert(&tr, atoi_check(argv[i]), NULL, 0);
	}
	tmpl = NULL;
	tree_to_lst(tr, &tmpl);
	//TODO free tree
	lst_to_array(tmpl, sorted_ar, count);
	ft_lstdel(&tmpl, NULL);
	init_razn(razn, sorted_ar, *in, count);
}

/*static int	find_shift(t_list **st, int count)
{
	int	shifts[count];
	int	i;
	int	max;
	int	i_max;
	t_list *cp;

	i = -1;
	while (++i < count)
		shifts[i] = 0;
	cp = *st;
	while (cp)
	{
		shifts[ICONT(cp) + count / 2]++;
		cp = cp->next;
	}
	i = -1;
	max = 0;
	i_max = 0;
	while (++i < count)
		if (shifts[i] > max || (shifts[i] == max && ABS(i - count / 2) < ABS(i_max - count / 2)))
		{
			max = shifts[i];
			i_max = i;
		}
	i = i_max - count / 2;
	cp = *st;
	count /= 2;
	while (cp)
	{
		max = ICONT(cp) - i;
		ICONT(cp) = (-count <= max && max <= count) ? max : max - 2 * count ;
		cp = cp->next;
	}
	return (i);
}*/

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
	printf("\nstand = %d\n", stand);
	return (standing);
}

static void	push_b(int *standing, t_list **comm, int count)
{
	int	i;

	i = -1;
	while (++i < count)
	{
		if (standing[i] == 0)
			ft_lstadd_back(comm, ft_lstnew("pb", 3));
		else if (standing[i] == -1)
		{
			ft_lstadd_back(comm, ft_lstnew("rra", 3));
			ft_lstadd_back(comm, ft_lstnew("sa", 3));
			ft_lstadd_back(comm, ft_lstnew("ra", 3));
			ft_lstadd_back(comm, ft_lstnew("ra", 3));
		}
		else
			ft_lstadd_back(comm, ft_lstnew("ra", 3));
	}
}

int			main(int argc, char **argv)
{
	t_list	*a;
	t_list	*b;
	t_list	*razn;
	int		*standing;
//	int		i;
	t_list	*comm;

	comm = NULL;
//	printf("argc = %d\n", argc);
	if (argc < 3)
		return (clean("Error\n"));
	a = NULL;
	b = NULL;
	razn = NULL;
	init_stacks(&a, &razn, argc - 1, argv);
//	print_stacks(a, razn);
//	printf(">>>%d\n", find_shift(&razn, argc - 1));
//	print_stacks(a, razn);
	standing = choise_standing(razn, argc - 1);
//	i = -1;
//	while (++i < argc - 1)
//		printf("/%d/", standing[i]);
	push_b(standing, &comm, argc - 1);
	comm_stacks(&a, &b, comm);
	print_stacks(a, b);
	printf("comm: %d\n", ft_lstlen(comm));
//	b = NULL;
//	comm = NULL;
//	check_stacks(a, b);
//	stacks_magic(&a, &b, &comm, argc - 1, 'a');
//	print_comm(comm);
	return (0);
}
