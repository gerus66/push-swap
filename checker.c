/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 14:24:19 by mbartole          #+#    #+#             */
/*   Updated: 2019/04/11 02:31:45 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

static void	check_stacks(t_list *st, int count, t_list *ya_st)
{
	int	prev;

	if (!st)
		return ;
	if (!st->next && count == 1)
		exit(clean(OK_M, (t_list *[]){st, ya_st}, 2));
	prev = *((int *)st->cont);
	st = st->next;
	count--;
	while (st && count--)
	{
		if (*((int *)st->cont) < prev)
			return ;
		else if (*((int *)st->cont) == prev)
			exit(clean(KO_M, (t_list *[]){st, ya_st}, 2));
		prev = *((int *)st->cont);
		st = st->next;
	}
	if (count == 0)
		exit(clean(OK_M, (t_list *[]){st, ya_st}, 2));
}

static char	switch_ops(t_list **a, t_list **b, char *line)
{
	char	fl;

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
	return (fl);
}

static void	handle_stacks(t_list **a, t_list **b, int count)
{
	char	*line;

	while (get_next_line(0, &line))
	{
		if (!ft_strcmp(line, ""))
		{
			free(line);
			return ;
		}
		if (!switch_ops(a, b, line))
		{
			free(line);
			exit(clean(ERR_M, (t_list *[]){*a, *b}, 2));
		}
		free(line);
		print_stacks(*a, *b);
		check_stacks(*a, count, *b);
	}
}

int			main(int argc, char **argv)
{
	t_list	*a;
	t_list	*b;
	int		count;

	if (argc < 2)
		return (0);
	a = NULL;
	b = NULL;
	count = argv_to_list(&a, argv, argc - 1, 0);
	print_stacks(a, b);
	handle_stacks(&a, &b, count);
	check_stacks(a, count, b);
	clean(KO_M, (t_list *[]){a, b}, 2);
	return (0);
}
