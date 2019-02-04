/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 14:24:19 by mbartole          #+#    #+#             */
/*   Updated: 2019/01/31 16:36:48 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

static int	clean(char *msg)//TODO free all
{
	ft_putstr(msg);
	return (0);
}

static void	check_stack(t_list *st, int count)
{
	int	fl;
	ssize_t	prev;

	if (!st || !st->next)
		return ;
	fl = 1;
	prev = *((ssize_t *)st->cont);
	st = st->next;
	count--;
	while (st && count--)
	{
		if (*((ssize_t *)st->cont) < prev)
			return ;
		else if (*((ssize_t *)st->cont) == prev)
			exit(clean(ERR_M));//TODO
		prev = *((ssize_t *)st->cont);
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
	count = argc - 1;;
	while (--argc)
		ft_lstadd(&a, ft_lstnew(argv[argc], ft_strlen(argv[argc])));
	b = a;//TODO free b
	if (!(a = ft_lstmap(b, atoi_stack)))
		exit(clean(ERR_M));//TODO
	//TODO check dublicates 
	check_stack(a, count);
	b = NULL;
	handle_stacks(&a, &b, count);
	return (0);
}
