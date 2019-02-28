/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_sequence.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 22:24:24 by mbartole          #+#    #+#             */
/*   Updated: 2019/02/27 17:56:47 by mbartole         ###   ########.fr       */
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

void		old_choose_sequence(int *razn, int **standing, int count, char fl)
{
	int	*standing_tmp;
	int	i;
	int stand;
	int	stand_tmp;
	int	fill[count];

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
			if (stand_tmp > stand)
			{
				free(*standing);
				*standing = standing_tmp;
				stand = stand_tmp;
			}
		}
	printf("select >>  %d << numbers\n", stand);
}
# define START -5
# define TERM -6


int		*copy_array(int *array)
{
	int	*new;
	int	len;
	int	j;

	len = 0;
	while (array[len] != TERM)
		len++;
	new = (int *)ft_memalloc(sizeof(int) * (len + 1));
	j = -1;
	while (++j <= len)
		new[j] = array[j];
	return (new);
}

int		len_array(int *array)
{
	int	len;

	len = 0;
	while (array[len] != TERM)
		len++;
	return (len);
}

int	count_of_magic(int *array)
{
	int	count;
	int	i;

	if (!array)
		return (0);
	count = 0;
	i = -1;
	while (array[++i] != TERM)
		if (array[i] == 1)
			count++;
	return (count);
}

void	print_ar(int *seq, char *mes)
{
	int j = -1;
	while (seq[++j] != TERM)
		printf(" %d", seq[j]);
	printf(" %d / %s\n", seq[j], mes);
}


int	*req_seq(t_list *stack, int *seq, int prev, char fl_break)
{
	int	i;
	int	len;
	int	*copy;
	int	first;
	int	last;

	i = 0;
	while (seq[i] != START && seq[i] != TERM)
		i++;
//	printf("i = %d fl_break = %d prev = %d cont = %d\n", i, fl_break, 
//			prev, ICONT(stack));
	if (seq[i] == TERM)
	{
	//	printf("desicion: \n");
//		print_ar(seq, "seq");
		first = 0;
		last = 0;
		i = 0;
		while (++i)
		{
			if (seq[i - 1] == 1 && !first)
				first = ICONT(stack);
			if (seq[i - 1] == 1)
				last = ICONT(stack);
			if (seq[i - 1] == TERM)
				break ;
			stack = stack->next;
		}
	//	printf("first: %d, last: %d, stack: %d      count: %d\n",
//				first, last, ICONT(stack), count_of_magic(seq));
		if (count_of_magic(seq) > 2 &&
				(last < first || (last > first && !fl_break)))
		{
	//		print_ar(seq, "!");
	//		printf("+++++++good!   %d\n", count_of_magic(seq));
			return (seq);
		}
		free(seq);
//		printf("------no:(\n");
		return (NULL);
	}
	else if (i == 0 || ICONT(stack) > prev)
	{
	//	printf("2nd!\n");
	//	print_ar(seq, "seq");
		copy = copy_array(seq);
		seq[i] = 0;
		seq[i + 1] = !seq[i + 1] ? START : TERM;
		copy[i] = 1;
		copy[i + 1] = !copy[i + 1] ? START : TERM;
	//	print_ar(copy, "copy");
		if ((seq = req_seq(stack->next, seq, prev, 0)))
			first = count_of_magic(seq);
		else
			first = 0;
		if ((copy = req_seq(stack->next, copy, ICONT(stack), 1)))
			last = count_of_magic(copy);
		else
			first = 0;
	//	printf("         first: %d, last: %d",first, last);
		if (!first && !last)
		{
	//		printf(" - NULL\n");
			free(seq);
			free(copy);
			return (NULL);
		}
		else if (first >= last)
		{
	//	printf("         first: %d, last: %d",first, last);
	//		printf(" - choose first\n");
			free(copy);
			return (seq);
		}
		else
		{
	//	printf("         first: %d, last: %d",first, last);
	//		printf(" - choose last\n");
			free(seq);
			return (copy);
		}
	}
	else if (!fl_break)
	{
	//	printf("3rd!\n");
	//	print_ar(seq, "seq");
		copy = copy_array(seq);
	//	fl_break = 1;
		seq[i] = 0;
		seq[i + 1] = !seq[i + 1] ? START : TERM;
		copy[i] = 1;
		copy[i + 1] = !copy[i + 1] ? START : TERM;
		if (( seq = req_seq(stack->next, seq, prev, 0)))
			first = count_of_magic(seq);
		else
			first = 0;
		if ( (copy = req_seq(stack->next, copy, ICONT(stack), 1)))
			last = count_of_magic(copy);
		else
			first = 0;
	//	printf("         first: %d, last: %d",first, last);
		if (!first && !last)
		{
//			printf(" - NULL\n");
			free(seq);
			free(copy);
			return (NULL);
		}
		else if (first >= last)
		{
//		printf("         first: %d, last: %d",first, last);
//			printf(" - choose first\n");
			free(copy);
			return (seq);
		}
		else
		{
//		printf("         first: %d, last: %d",first, last);
//			printf(" - choose last\n");
			free(seq);
			return (copy);
		}
	}
//	printf("..default\n");
	seq[i] = 0;
	seq[i + 1] = !seq[i + 1] ? START : TERM;
	return (req_seq(stack->next, seq, prev, fl_break));
}


void	choose_sequence(int count, t_list *stack, int **standing)
{
	int	*magic;
	t_list *cp;
	int	*res;

	magic = (int *)ft_memalloc(sizeof(int) * (count + 1)); //init array
	magic[0] = START;
	magic[count] = TERM;
	cp = stack;                            // cycle stack
	while (cp->next)
		cp = cp->next;
	cp->next = stack;
	res = req_seq(stack, magic, 0, 0);
	printf("\nRESULT:   %d\n", count_of_magic(res));
	print_ar(res, "!");
	standing = &res;
}


