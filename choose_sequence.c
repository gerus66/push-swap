/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_sequence.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 22:24:24 by mbartole          #+#    #+#             */
/*   Updated: 2019/04/01 21:50:10 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

static void	improve_razn(int *razn, int len, char fl)
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

static int	*positive_seq(int *razn, int start, int count, char fll)
{
	int	*standing;
	int	i;
	int	last;
	int	prev;
	int	fl;

	if (!(standing = (int *)ft_memalloc(sizeof(int) * count)))
		return (NULL);
	improve_razn(razn, count, 1);
	standing[start] = 1;
	last = razn[start];
	prev = count;//
	i = start;//
	fl = 0;
	while (++i < count)
	{
//		printf("razn[i] %3d | last %3d | prev %3d \n", razn[i], last, prev);
		if (razn[i] <= last && razn[i] >= 0
				&& razn[i] >= razn[start] - start - (count - i - 1))//
		{
			fl++;
			standing[i] = 1;
			prev = last;
			last = razn[i];
		}
		else if (razn[i] > last && razn[i] <= prev && (fll == 1))
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
	improve_razn(razn, count, -1);
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
		else if (razn[i] > last && razn[i] <= prev && (fll == 1))
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

void		choose_sequence(int *razn, int **standing, int count, char fl)
{
	int	*standing_tmp;
	int	i;
	int stand;
	int	stand_tmp;
	int	fill[count];

	i = -1;
	while (++i < count)
		printf("/%d/", razn[i]);
	printf("\n");
	if (count == 1 || count == 2)
	{
		if (!(*standing = (int *)malloc(sizeof(int) * count)))
			return ;
		i = -1;
		while (++i < count)
			(*standing)[i] = 1;
		return ;
	}
	i = -1;
	while (++i < count)
		fill[i] = 0;
	*standing = NULL;
	stand = 0;
	i = -1;
	while (++i < count - stand)
		if (!fill[i])
		{
			standing_tmp = (razn[i] <= 0) ? negative_seq(razn, i, count, fl) :
				positive_seq(razn, i, count, fl);
			stand_tmp = stand_count(standing_tmp, count);
			add_array(fill, standing_tmp, count);
			if (stand_tmp >= stand)
			{
				free(*standing);
				*standing = standing_tmp;
				stand = stand_tmp;
			}
		}
	i = -1;
	while (++i < count)
		printf("%d ", (*standing)[i]);
	printf("\n");
	free(razn);
}
