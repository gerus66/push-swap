/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 14:24:19 by mbartole          #+#    #+#             */
/*   Updated: 2019/04/22 16:15:18 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

static void		handle_stacks(t_stacks *st, int count, char print)
{
	char	*line;
	int		ret;

	if (print & 1)
		print_stacks(st->a, st->b, print & 2 ? 12 : 0, 22);
	while (get_next_line(0, &line))
	{
		if (print & 1)
			ft_printf(print & 2 ? "{fma}%s{eoc}\n" : "%s\n", line);
		ret = code_comm(line, 0, 0);
		do_one_comm(st, line, 1, 0);
		if (print & 1)
			print_stacks(st->a, st->b, print & 2 ? ret : 0, 22);
		ret = check_stacks(st->a, count);
		if (ret == 2)
			exit(clean(KO_M, st));
	}
}

static void		no_graph(t_stacks *st, int count, char opt)
{
	handle_stacks(st, count, opt);
	if (check_stacks(st->a, count) == 1)
		exit(clean(OK_M, st));
}

/*
** bits of [print]:
** [-g(raphics)|-c(olor)|-v(izual)]
*/

int				main(int argc, char **argv)
{
	t_stacks	st;
	int			count;
	char		opt;

	opt = 0;
	while (argc > 1 && (!ft_strcmp("-v", *(argv + 1)) ||
			!ft_strcmp("-c", *(argv + 1))))
	{
		if (!ft_strcmp("-v", *(argv + 1)))
			opt = opt | 1;
		if (!ft_strcmp("-c", *(argv + 1)))
			opt = opt | 2;
		argv++;
		argc--;
	}
	if (argc < 2)
		return (0);
	init_all(&st, argv, argc - 1, 0);
	count = st.len_a;
	no_graph(&st, count, opt);
	return (clean(KO_M, &st));
}
