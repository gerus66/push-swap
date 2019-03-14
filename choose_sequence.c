/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_sequence.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 22:24:24 by mbartole          #+#    #+#             */
/*   Updated: 2019/03/14 23:15:47 by mbartole         ###   ########.fr       */
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

//	i = -1;
//	while (++i < count)
//		printf("%d ", razn[i]);
//	printf("\n");
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
	i = -1;
	while (++i < count)
		printf("%d ", (standing)[i]);
	printf("\n");
	free(razn);
	return (standing);
}

void	init_push_and_stay(t_list *st, t_list **push, t_list **stay,
		char include_swap)
{
	int		i;
	int		count;
	int		*seq;

	seq = choose_sequence(get_diff(st, 1), ft_lstlen(st), include_swap);
	count = ft_lstlen(st);
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
}
