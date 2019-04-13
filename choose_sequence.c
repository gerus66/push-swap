/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_sequence.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 22:24:24 by mbartole          #+#    #+#             */
/*   Updated: 2019/04/12 16:27:21 by mbartole         ###   ########.fr       */
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

static int		stand_count(int *ar, int count)
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

static int		*general_seq(int *razn, int start, int count, char pos)
{
	int	*standing;
	int	i;
	int	last;
	int	prev;

	if (!(standing = (int *)ft_memalloc(sizeof(int) * count)))
		return (NULL);
	standing[start] = 1;
	last = razn[start];
	prev = pos ? count : 0;
	i = start;
	while (++i < count)
	{
		if (razn[i] <= last && ((razn[i] >= 0 && pos) || !pos) &&
				razn[i] >= razn[start] - start - (count - i - 1))
		{
			standing[i] = 1;
			prev = last;
			last = razn[i];
		}
		else if (razn[i] > last && razn[i] <= prev)
		{
			if (stand_count(standing, count) == 1)
				start = i;
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

static void		add_array(int *ar, int *add, int count)
{
	int	i;

	i = -1;
	while (++i < count)
		if (add[i])
			ar[i] = 1;
}

void			choose_sequence(int *razn, int count)
{
	int *standing;
	int	*standing_tmp;
	int	i;
	int stand;
	int	stand_tmp;
	int	fill[count];

	i = -1;
	while (++i < count)
		fill[i] = 0;
	standing = NULL;
	stand = 0;
	i = -1;
	while (++i < count - stand)
		if (!fill[i])
		{
			improve_razn(razn, count, razn[i] <= 0 ? 0 : 1);
			standing_tmp = general_seq(razn, i, count, razn[i] <= 0 ? 0 : 1);
			stand_tmp = stand_count(standing_tmp, count);
			add_array(fill, standing_tmp, count);
			if (stand_tmp >= stand && (stand = stand_tmp))
			{
				free(standing);
				standing = standing_tmp;
			}
		}
	i = -1;
	while (++i < count)
		razn[i] = standing[i];
	free(standing);
}
