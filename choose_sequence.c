/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_sequence.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 22:24:24 by mbartole          #+#    #+#             */
/*   Updated: 2019/03/16 20:52:48 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

static int	*positive_seq(int *razn, int start, int count, char fll)
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
		else if (razn[i] > last && razn[i] <= prev && fll)
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

static int	*negative_seq(int *razn, int start, int count, char fll)
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
		else if (razn[i] > last && razn[i] <= prev && fll)
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

int			*choose_sequence(int *razn, int count, char include_swap)
{
	int	*standing;
	int	*standing_tmp;
	int	i;
	int stand;
	int	stand_tmp;
	int	fill[count];

	if (count < 3)
	{
		if (!(standing = (int *)malloc(sizeof(int) * count)))
			return (NULL);
		i = -1;
		while (++i < count)
			standing[i] = 1;
		return (standing);
	}
	i = -1;
	while (++i < count)
		fill[i] = 0;
	standing = NULL;
	stand = 0;
	i = -1;
	while (++i < count - stand)
		if (!fill[i])
		{
			standing_tmp = (razn[i] <= 0) ? negative_seq(razn, i, count, 
					include_swap) :
				positive_seq(razn, i, count, include_swap);
			stand_tmp = stand_count(standing_tmp, count);
			add_array(fill, standing_tmp, count);
			if (stand_tmp > stand)
			{
				free(standing);
				standing = standing_tmp;
				stand = stand_tmp;
			}
		}
	free(razn);
	return (standing);
}

static void	adjust_stay_to_st(t_list *st, t_list **stay)
{
	int	i;
	int	count;

	count = ft_lstlen(*stay);
	i = -1;
	while (++i < count)
	{
		if (ICONT(st) == ICONT(*stay))
			return ;
		do_one_comm(stay, NULL, ft_lstnew("ra", 3));
	}
	adjust_stay_to_st(st->next, stay);
}

static int	*get_sequence(t_list *st, t_list *to_stay, int count)
{
	int	*seq;
	int	i;

//	printf("GET SEQUENSE\n");
//	print_stacks(st, to_stay);
	if (!(seq = ft_memalloc(sizeof(int) * count)))
		return (NULL);
	i = -1;
	while (++i < count && to_stay)
	{
//		printf("st: %d  stay: %d\n", ICONT(st), ICONT(to_stay));
		seq[i] = (ICONT(st) == ICONT(to_stay)) ? 1 : 0;
		if (seq[i])
			to_stay = to_stay->next;
		st = st->next;
	}
//	i = -1;//
//	while (++i < count)//
//		printf("%d ", (seq)[i]);//
//	printf("\n");//
	return (seq);
}

void	init_push_and_stay(t_list *st, t_list **push, t_list **stay,
		char include_swap)
{
	int		i;
	int		count;
	int		*seq;

	count = ft_lstlen(st);
	if (!(*stay))
		seq = choose_sequence(get_diff(st, 1), count, include_swap);
	else
	{
		adjust_stay_to_st(st, stay);
		seq = get_sequence(st, *stay, count);
	}
	*push = NULL;
	*stay = NULL;
	i = -1;
	while (++i < count)
	{
		if (seq[i])
			ft_lstadd_back(stay,ft_lstnew(st->cont, sizeof(int)));
		else
			ft_lstadd_back(push,ft_lstnew(st->cont, sizeof(int)));
		st = st->next;
	}
	i = -1;//
	while (++i < count)//
		printf("%d ", (seq)[i]);//
	printf("\n");//
}
