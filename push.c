/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 20:06:05 by mbartole          #+#    #+#             */
/*   Updated: 2019/02/25 20:14:09 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

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
