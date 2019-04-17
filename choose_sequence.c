/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_sequence.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 22:24:24 by mbartole          #+#    #+#             */
/*   Updated: 2019/04/17 19:00:04 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

/*
** param[0] last
** param[1] prev - no matter
** param[2] i
** param[3] first
*/

static int		*init_st(int *razn, int len, int k, int **param)
{
	int		*st;
	int		i;

	if (!(st = (int *)ft_memalloc(sizeof(int) * len)))
		return (NULL);
	st[k] = 1;
	i = k;
	while (++i < len)
	{
		if ((razn[k] > 0 && razn[i] * (-2) == len) ||
			(razn[k] <= 0 && razn[i] * 2 == len))
			razn[i] = -razn[i];
	}
	*param[0] = razn[k];
	*param[1] = 0;
	*param[2] = k;
	*param[3] = 1;
	return (st);
}

/*
** lst[0] last
** lst[1] prev
*/

static int		*general_seq(int *r, int k, int count, int first)
{
	int		*st;
	int		i;
	int		lst[2];

	if (!(st = init_st(r, count, k, (int*[]){&lst[0], &lst[1], &i, &first})))
		return (NULL);
	while (++i < count)
	{
		lst[0]++;
		lst[1]++;
		if (r[i] <= lst[0] && r[i] >= r[k] - k - (count - i - 1) && (st[i] = 1))
		{
			lst[1] = lst[0];
			lst[0] = r[i];
			first = 0;
		}
		else if (((r[i] > lst[0] && (r[i] <= lst[1] || first)) || count == 3)
					&& (st[i] = -1))
		{
			lst[1] = r[i];
			k = first ? i : k;
			first = 0;
		}
	}
	return (st);
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
	if (new_stand > stand)
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
			if (!(st_tmp = general_seq(razn, i, count, 0)))
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
