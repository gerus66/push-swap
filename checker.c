/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 14:24:19 by mbartole          #+#    #+#             */
/*   Updated: 2019/01/27 02:10:55 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

#define CONT_SIZE 8
#define I_MAX 2147483647
#define I_MIN -2147483648


static void	clean(char *msg)//TODO free all
{
	ft_putstr(msg);
	exit(0);
}

void		print_stacks(t_list *a, t_list *b)
{
	while (a || b)
	{
		printf("%6zu %6zu\n", (a ? *((ssize_t *)a->cont) : 0), 
				(b ? *((ssize_t *)b->cont) : 0));
		if (a)
			a = a->next;
		if (b)
			b = b->next;
	}
	printf("%6c %6c\n", '_', '_');
	printf("%6c %6c\n\n", 'a', 'b');
}

t_list		*atoi_stack(t_list *stack)
{
	ssize_t	res;
	char	sign;
	char	*s;

	res = 0;
	s = (char *)stack->cont;
	sign = (*s == '-' ? -1 : 1);
	if (*s == '-' || *s == '+')
		s++;
	while (*s)
	{
		if (*s >= '0' && *s <= '9')
			res = res * 10 + *s - 48;
		else
			return (NULL);
		s++;
	}
	res *= sign;
	if (res > I_MAX || res < I_MIN)
		return (NULL);
	return (ft_lstnew((void *)&res, sizeof(ssize_t)));
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
			clean(ERR_M);//TODO
		prev = *((ssize_t *)st->cont);
		st = st->next;
	}
	if (count == 0)
		clean("OK\n");//TODO
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
			clean(ERR_M);//TODO
		free(line);
		print_stacks(*a, *b);
		check_stack(*a, count);
//		printf("waiting instructions\n");
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
		clean(ERR_M);//TODO
	//TODO check dublicates 
	check_stack(a, count);
	b = NULL;
	handle_stacks(&a, &b, count);
	return (0);
}
