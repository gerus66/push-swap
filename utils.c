/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 12:41:17 by mbartole          #+#    #+#             */
/*   Updated: 2019/04/13 14:22:56 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

/*
** clean [count] lists, print message
*/

int clean(char *msg, t_stacks *all)
{
	ft_lstdel(&all->a, NULL);
	ft_lstdel(&all->b, NULL);
	ft_lstdel(&all->comm, NULL);
	ft_putstr(msg);
	return (0);
}

int     last_elem(t_list *stack)
{
	if (!stack)
		return (0);
	while (stack->next)
		stack = stack->next;
	return (ICONT(stack));
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

void		print_stack(t_list *a)
{
	while (a)
	{
		printf("%2d ", ICONT(a));
			a = a->next;
	}
	printf("\n");
}

void	print_comm(t_list *comm)
{
	t_list	*tmp;

	tmp = comm;
	while (comm)
	{
		printf("%s\n", CCONT(comm));
		comm = comm->next;
	}
//	printf(" // count: %d\n", ft_lstlen(tmp));
}

void	print_seq(int *seq, int count)
{
	int i = -1;
	while (++i < count)
		printf("%2d ", seq[i]);
	printf("\n");
}

int	cut_tail(t_list **comm, char *name)
{
	t_list	*tmp;
	t_list	*del;

	if (!comm || !(*comm))
		return(0);
	if (!(*comm)->next && !ft_strcmp(CCONT(*comm), name))
	{
		free(*comm);
		*comm = NULL;
		return(0) ;
	}
	tmp = *comm;
	while (tmp->next && tmp->next->next)
		tmp = tmp->next;
	if (ft_strcmp(CCONT(tmp), name) || ft_strcmp(CCONT(tmp->next), name))
		return(0) ;
	del = tmp->next;
	tmp->next = NULL;
	ft_lstdelone(&del, NULL);
	return (1 + cut_tail(comm, name));
}

char    can_insert(int val, int first, int last)
{
	if ((val < first && val > last) ||
			(val > first && val > last && first < last)
			|| (val < first && first < last))
		return (1);
	return (0);
}

char    can_insert_rev(int val, t_list *st)
{
	if ((val > ICONT(st) && val < last_elem(st)) ||
			(val < ICONT(st) && val < last_elem(st) && ICONT(st) > last_elem(st))
			|| (val > ICONT(st) && ICONT(st) > last_elem(st)))
		return (1);
	return (0);
}

t_list	*get_to_push(int *seq, t_list *st)
{
	int		i;
	int		count;
	t_list	*to_push;

	count = ft_lstlen(st);
	to_push = NULL;
	i = -1;
	while (++i < count)
	{
		if (seq[i] == 0)
			ft_lstadd_back(&to_push,ft_lstnew(st->cont, sizeof(int)));
		st = st->next;
	}
	return (to_push);
}
