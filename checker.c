/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 14:24:19 by mbartole          #+#    #+#             */
/*   Updated: 2019/04/15 23:37:36 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

static void	print_stacks(t_list *a, t_list *b, int comm, int first)
{
	int		div;

	div = ft_lstlen(a) - ft_lstlen(b);
	while (a || b)
	{
		if (div >= 0 && ft_printf((comm && comm % 10 != 2 && ((first / 10 &&
			comm / 10 != 3) || (!a->next && comm / 10 == 3))) ?
			"{bgn}{fgr}%6d{eoc} " : "%6d ", ICONT(a), first =
			(first / 10 == 2 && comm / 10 == 1) ? first - 10 : first % 10))
			a = a->next;
		else
			ft_printf("%6c ", ' ');
		if (div <= 0 && ft_printf((comm && comm % 10 != 1 && ((first % 10 &&
			comm / 10 != 3) || (!b->next && comm / 10 == 3))) ?
			"{bgn}{fgr}%6d{eoc}\n" : "%6d\n", ICONT(b),
			first -= (first % 10 == 2 && comm / 10 == 1) ? 1 : first % 10))
			b = b->next;
		else
			ft_printf("%6c\n", ' ');
		if (div > 0)
			div--;
		if (div < 0)
			div++;
	}
	ft_printf("%6c %6c\n%6c %6c\n\n", '_', '_', 'a', 'b');
}

static int	check_stacks(t_list *st, int count)
{
	int	prev;

	if (!st)
		return (0);
	if (!st->next && count == 1)
		return (1);
	prev = *((int *)st->cont);
	st = st->next;
	count--;
	while (st && count--)
	{
		if (*((int *)st->cont) < prev)
			return (0);
		else if (*((int *)st->cont) == prev)
			return (2);
		prev = *((int *)st->cont);
		st = st->next;
	}
	if (count == 0)
		return (1);
	return (0);
}

static void	handle_stacks(t_stacks *st, int count, char print)
{
	char	*line;
	int		ret;

	if (print)
		print_stacks(st->a, st->b, 0, 22);
	while (get_next_line(0, &line))
	{
		if (!ft_strcmp(line, ""))
		{
			free(line);
			return ;
		}
		if (print)
			ft_printf("{fma}%s{eoc}\n", line);
		ret = do_one_comm(st, line, 1, 0);
		if (print)
			print_stacks(st->a, st->b, print % 10 ? ret : 0, 22);
		ret = check_stacks(st->a, count);
		if (ret == 1)
			exit(clean(OK_M, st));
		if (ret == 2)
			exit(clean(KO_M, st));
	}
}

int			main(int argc, char **argv)
{
	t_stacks	st;
	int			count;

	if (argc < 2)
		return (0);
	init_all(&st, argv, argc - 1, 0);
	count = st.len_a;
	handle_stacks(&st, count, 11);
	if (check_stacks(st.a, count) == 1)
		return (clean(OK_M, &st));
	return (clean(KO_M, &st));
}
