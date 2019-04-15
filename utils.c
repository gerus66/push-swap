/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 12:41:17 by mbartole          #+#    #+#             */
/*   Updated: 2019/04/15 14:19:11 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

int		clean(char *msg, t_stacks *all)
{
	ft_lstdel(&all->a, NULL);
	ft_lstdel(&all->b, NULL);
	ft_lstdel(&all->comm, NULL);
	ft_putstr(msg);
	return (0);
}

int		last_elem(t_list *stack)
{
	if (!stack)
		return (0);
	while (stack->next)
		stack = stack->next;
	return (ICONT(stack));
}

int		cut_tail(t_list **comm, char *name)
{
	t_list	*tmp;
	t_list	*del;

	if (!comm || !(*comm))
		return (0);
	if (!(*comm)->next && !ft_strcmp(CCONT(*comm), name))
	{
		free(*comm);
		*comm = NULL;
		return (0);
	}
	tmp = *comm;
	while (tmp->next && tmp->next->next)
		tmp = tmp->next;
	if (ft_strcmp(CCONT(tmp), name) || ft_strcmp(CCONT(tmp->next), name))
		return (0);
	del = tmp->next;
	tmp->next = NULL;
	ft_lstdelone(&del, NULL);
	return (1 + cut_tail(comm, name));
}

char	can_insert(int val, int first, int last)
{
	if ((val < first && val > last) ||
			(val > first && val > last && first < last)
			|| (val < first && first < last))
		return (1);
	return (0);
}

char	can_insert_rev(int val, t_list *st)
{
	if ((val > ICONT(st) && val < last_elem(st)) ||
		(val < ICONT(st) && val < last_elem(st) && ICONT(st) > last_elem(st))
		|| (val > ICONT(st) && ICONT(st) > last_elem(st)))
		return (1);
	return (0);
}
