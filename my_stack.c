/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_comm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 18:51:58 by mbartole          #+#    #+#             */
/*   Updated: 2019/02/04 10:27:32 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

#define I_MAX 2147483647
#define I_MIN -2147483648

void	swap_stack(t_list **st)
{
	t_list	*tmp;

	if (!(*st) || !(*st)->next)
		return ;
	tmp = (*st)->next;
	(*st)->next = (*st)->next->next;
	tmp->next = *st;
	*st = tmp;
}

void	push_stack(t_list **src, t_list **dst)
{
	t_list	*tmp;

	if (!(*src))
		return ;
	tmp = (*src)->next;
	(*src)->next = (*dst);
	*dst = *src;
	*src = tmp;
}

void	rotate_stack(t_list **st)
{
	t_list	*tmp;

	if (!(*st) || !(*st)->next)
		return ;
	tmp = *st;
	while ((*st)->next)
		*st = (*st)->next;
	(*st)->next = tmp;
	*st = tmp->next;
	tmp->next = NULL;
}

void	r_rotate_stack(t_list **st)
{
	t_list	*tmp;

	if (!(*st) || !(*st)->next)
		return ;
	tmp = *st;
	while ((*st)->next->next)
		*st = (*st)->next;
	(*st)->next->next = tmp;
	tmp = (*st)->next;
	(*st)->next = NULL;
	*st = tmp;
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
