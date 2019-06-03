/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   improve_comm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 12:47:32 by mbartole          #+#    #+#             */
/*   Updated: 2019/04/15 13:36:18 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

static void		del_next(t_list *cur)
{
	t_list	*tmp;

	tmp = cur->next;
	cur->next = cur->next->next;
	ft_lstdelone(&tmp, NULL);
}

static char		need_improve_swap(t_list *cur, char letter)
{
	if (cur && cur->next && cur->next->next &&
			(!ft_strcmp(CCONT(cur), letter == 'a' ? "ra" : "rb") &&
			!ft_strcmp(CCONT(cur->next), letter == 'a' ? "pa" : "pb") &&
			!ft_strcmp(CCONT(cur->next->next), letter == 'a' ? "rra" : "rrb")))
		return (1);
	return (0);
}

void			improve_comm_swap(t_list **comm)
{
	t_list	*cur;

	cur = *comm;
	while (cur && cur->next && cur->next->next && cur->next->next->next)
	{
		if (need_improve_swap(cur->next, 'a'))
		{
			del_next(cur);
			cur = cur->next->next;
			ft_memcpy(cur->cont, (void *)"sa", sizeof(char) * 3);
		}
		cur = cur->next;
	}
	cur = *comm;
	while (cur && cur->next && cur->next->next && cur->next->next->next)
	{
		if (need_improve_swap(cur->next, 'b'))
		{
			del_next(cur);
			cur = cur->next->next;
			ft_memcpy(cur->cont, (void *)"sb", sizeof(char) * 3);
		}
		cur = cur->next;
	}
}

static char		need_improve_dub(t_list *cur)
{
	if (cur && cur->next && (
		(!ft_strcmp(CCONT(cur), "ra") && !ft_strcmp(CCONT(cur->next), "rra")) ||
		(!ft_strcmp(CCONT(cur), "rra") && !ft_strcmp(CCONT(cur->next), "ra")) ||
		(!ft_strcmp(CCONT(cur), "rb") && !ft_strcmp(CCONT(cur->next), "rrb")) ||
		(!ft_strcmp(CCONT(cur), "rrb") && !ft_strcmp(CCONT(cur->next), "rb"))))
		return (1);
	return (0);
}

void			improve_comm_dub(t_list **comm)
{
	t_list	*tmp;
	t_list	*cur;

	if (need_improve_dub(*comm))
	{
		tmp = *comm;
		*comm = (*comm)->next;
		ft_lstdelone(&tmp, NULL);
		tmp = *comm;
		*comm = (*comm)->next;
		ft_lstdelone(&tmp, NULL);
		improve_comm_dub(comm);
	}
	cur = *comm;
	while (cur && cur->next && cur->next->next)
	{
		if (need_improve_dub(cur->next))
		{
			del_next(cur);
			del_next(cur);
		}
		cur = cur->next;
	}
}
