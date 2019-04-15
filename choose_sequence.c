/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_sequence.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 22:24:24 by mbartole          #+#    #+#             */
/*   Updated: 2019/04/15 18:25:11 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

static void		improve_razn(int *razn, int len, char fl)
{
	int	i;

	i = -1;
	while (++i < len)
	{
		if ((fl == 1 && razn[i] * (-2) == len) ||
			(fl == -1 && razn[i] * 2 == len))
			razn[i] = -razn[i];
	}
}

static int		*general_seq(int *razn, int start, int count, char pos)
{
	int		*standing;
	int		i;
	int		last;
	int		prev;
	char	first;

	if (!(standing = (int *)ft_memalloc(sizeof(int) * count)))
		return (NULL);
	standing[start] = 1;
	last = razn[start];
	prev = pos ? count : 0;
	i = start;
	first = 1;
	while (++i < count)
	{
		if (razn[i] <= last && ((razn[i] >= 0 && pos) || !pos) &&
				razn[i] >= razn[start] - start - (count - i - 1))
		{
			standing[i] = 1;
			prev = last + 1;
			last = razn[i] + 1;
			first = 0;
		}
		else if (razn[i] > last && razn[i] <= prev)
		{
			if (first)
			{
				first = 0;
				start = i;
			}
			prev = razn[i];
			standing[i] = -1;
			last++;
		}
		else
		{
			last++;
			prev++;
		}
	}
	return (standing);
}

static void		fill_it(int *ar, int *add, int count, char copy)
{
	int	i;

	i = -1;
	if (!add)
	{
		while (++i < count)
			ar[i] = 0;
		return ;
	}
	if (copy)
	{
		while (++i < count)
			ar[i] = add[i];
		return ;
	}
	while (++i < count)
		if (add[i])
			ar[i] = 1;
}

static int		swap_it(int **new, int **old, int count, int stand)
{
	int	new_stand;
	int	i;

	new_stand = 0;
	i = -1;
	while (++i < count)
		if ((*new)[i])
			new_stand++;
	if (new_stand >= stand)
	{
		ft_swap_p((void **)new, (void **)old);
		return (new_stand);
	}
	return (stand);
}

void			choose_sequence(int *razn, int count, t_stacks *all)
{
	int *standing;
	int	*st_tmp;
	int	i;
	int stand;
	int	fill[count];

	fill_it(fill, NULL, count, 0);
	standing = NULL;
	stand = 0;
	i = -1;
	while (++i < count - stand)
		if (!fill[i])
		{
			improve_razn(razn, count, razn[i] <= 0 ? 0 : 1);
			if (!(st_tmp = general_seq(razn, i, count, razn[i] <= 0 ? 0 : 1)))
			{
				free(standing);
				exit(clean(ERM_M, all));
			}
			stand = swap_it(&st_tmp, &standing, count, stand);
			fill_it(fill, st_tmp, count, 0);
			free(st_tmp);
		}
	fill_it(razn, standing, count, 1);
	free(standing);
}
