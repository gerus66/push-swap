/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 14:24:19 by mbartole          #+#    #+#             */
/*   Updated: 2019/04/15 15:00:46 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

static void	print_stacks(t_list *a, t_list *b)
{
	while (a || b)
	{
		ft_printf("%6d %6d\n", (a ? ICONT(a) : 0),
				(b ? ICONT(b) : 0));
		if (a)
			a = a->next;
		if (b)
			b = b->next;
	}
	ft_printf("%6c %6c\n", '_', '_');
	ft_printf("%6c %6c\n\n", 'a', 'b');
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

static void	handle_stacks(t_stacks *st, int count)
{
	char	*line;
	int		ret;

	while (get_next_line(0, &line))
	{
		if (!ft_strcmp(line, ""))
		{
			free(line);
			return ;
		}
		do_one_comm(st, line, 1);
		print_stacks(st->a, st->b);
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
	print_stacks(st.a, st.b);
	handle_stacks(&st, count);
	if (check_stacks(st.a, count) == 1)
		return (clean(OK_M, &st));
	return (clean(KO_M, &st));
}
