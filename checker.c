/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 14:24:19 by mbartole          #+#    #+#             */
/*   Updated: 2019/04/10 05:17:45 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

static void	check_stack(t_list *st, int count)
{
	int	fl;
	int	prev;

	if (!st || !st->next)
		return ;
	fl = 1;
	prev = *((int *)st->cont);
	st = st->next;
	count--;
	while (st && count--)
	{
		if (*((int *)st->cont) < prev)
			return ;
		else if (*((int *)st->cont) == prev)
			exit(clean(ERR_M));//TODO
		prev = *((int *)st->cont);
		st = st->next;
	}
	if (count == 0)
		exit(clean("OK\n"));//TODO
}

static void	handle_stacks(t_list **a, t_list **b, int count)
{
	char	*line;
	int		fl;

	print_stacks(*a, *b);
	while (get_next_line(0, &line))
	{
		fl = 0;
		if ((!ft_strcmp(line, "sa") || !ft_strcmp(line, "ss")) && (fl = 1))
			swap_stack(a);
		if ((!ft_strcmp(line, "sb") || !ft_strcmp(line, "ss")) && (fl = 1))
			swap_stack(b);
		if ((!ft_strcmp(line, "ra") || !ft_strcmp(line, "rr")) && (fl = 1))
			rotate_stack(a);
		if ((!ft_strcmp(line, "rb") || !ft_strcmp(line, "rr")) && (fl = 1))
			rotate_stack(b);
		if ((!ft_strcmp(line, "rra") || !ft_strcmp(line, "rrr")) && (fl = 1))
			r_rotate_stack(a);
		if ((!ft_strcmp(line, "rrb") || !ft_strcmp(line, "rrr")) && (fl = 1))
			r_rotate_stack(b);
		if (!ft_strcmp(line, "pa") && (fl = 1))
			push_stack(b, a);
		else if (!ft_strcmp(line, "pb") && (fl = 1))
			push_stack(a, b);
		if (!fl)
			exit(clean(ERR_M));//TODO
		free(line);
		print_stacks(*a, *b);
		check_stack(*a, count);
	}
	exit(clean(ERR_M));
}

int			main(int argc, char **argv)
{
	t_list	*a;
	t_list	*b;
	int		count;

	if (argc == 2)
		write(1, "OK\n", 3);
	if (argc < 3)
		return (0);
	count = argv_to_list(&a, argv, argc - 1, 0);
	//TODO check dublicates 
	check_stack(a, count);
	b = NULL;
	handle_stacks(&a, &b, count);
	return (0);
}
