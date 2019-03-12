/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 12:41:17 by mbartole          #+#    #+#             */
/*   Updated: 2019/03/12 18:48:14 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

int clean(char *msg)
{
	ft_putstr(msg);
	return (0);
}

int     last_elem(t_list *stack)
{
	while (stack->next)
		stack = stack->next;
	return (ICONT(stack));
}

int		atoi_check(char *s)
{
	ssize_t	res;
	char	sign;

	res = 0;
	sign = (*s == '-' ? -1 : 1);
	if (*s == '-' || *s == '+')
		s++;
	while (*s)
	{
		if (*s >= '0' && *s <= '9')
			res = res * 10 + *s - 48;
		else
			exit(clean(ERR_M));//TODO
		s++;
	}
	res *= sign;
	if (res > I_MAX || res < I_MIN)
		exit(clean(ERR_M));//TODO
	return ((int)res);
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

void		print_stacks(t_list *a, t_list *b)
{
	while (a || b)
	{
		printf("%6d %6d\n", (a ? ICONT(a) : 0),
				(b ? ICONT(b) : 0));
		if (a)
			a = a->next;
		if (b)
			b = b->next;
	}
	printf("%6c %6c\n", '_', '_');
	printf("%6c %6c\n\n", 'a', 'b');
}

void	do_one_comm(t_list **a, t_list **b, t_list *comm)
{
	char	*line;
	int		fl;

	fl = 0;
	line = (char *)comm->cont;
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
}

void	do_one_chaos_comm(t_list **a, t_list **b, t_list *comm)
{
	if (*b && (*b)->next)
	{
		if (!(ft_strcmp(CCONT(comm), "sa")))
			ft_memcpy(comm->cont, (void *)"ss", sizeof(char *));
		else if (!(ft_strcmp(CCONT(comm), "ra")))
			ft_memcpy(comm->cont, (void *)"rr", sizeof(char *));
		else if (!(ft_strcmp(CCONT(comm), "rra")))
			ft_memcpy(comm->cont, (void *)"rrr", sizeof(char *));
	}
	do_one_comm(a, b, comm);
}

void	do_all_comm(t_list **a, t_list **b, t_list *comm, char chaos)
{
	while (comm)
	{
		if (chaos)
			do_one_chaos_comm(a, b, comm);
		else
			do_one_comm(a, b, comm);
		comm = comm->next;
	}
}
