/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_to_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 08:07:46 by mbartole          #+#    #+#             */
/*   Updated: 2019/04/05 08:02:10 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

static char	need_improve(t_list	*cur)
{
	if (cur && cur->next &&
			((!ft_strcmp(CCONT(cur), "ra") && !ft_strcmp(CCONT(cur->next), "rra")) ||
			 (!ft_strcmp(CCONT(cur), "rra") && !ft_strcmp(CCONT(cur->next), "ra")) ||
			 (!ft_strcmp(CCONT(cur), "rb") && !ft_strcmp(CCONT(cur->next), "rrb")) ||
			 (!ft_strcmp(CCONT(cur), "rrb") && !ft_strcmp(CCONT(cur->next), "rb"))))
		return (1);
	return (0);
}

void	improve_comm_dub(t_list **comm)
{
	t_list	*tmp;
	t_list	*cur;

	if (need_improve(*comm))
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
		if (need_improve(cur->next))
		{
			tmp = cur->next;
			cur->next = cur->next->next;
			ft_lstdelone(&tmp, NULL);
			tmp = cur->next;
			cur->next = cur->next->next;
			ft_lstdelone(&tmp, NULL);
		}
		cur = cur->next;
	}
}

t_list	*push_b(int *standing, t_list **a, t_list **b)
{
	int		i;
	int		count;
	t_list	*comm;
	t_list	*tmp;
	char	fl;

	comm = NULL;
	count = ft_lstlen(*a);
	i = -1;
	tmp = *a;
	while (++i < count)
	{
		if (standing[i] == 0)
			ft_lstadd_back(&comm, ft_lstnew("pb", 3));
		else if (standing[i] == -1)
		{
			ft_lstadd_back(&comm, ft_lstnew("rra", 4));
			ft_lstadd_back(&comm, ft_lstnew("sa", 3));
			ft_lstadd_back(&comm, ft_lstnew("ra", 3));
			ft_lstadd_back(&comm, ft_lstnew("ra", 3));
		}
		else
			ft_lstadd_back(&comm, ft_lstnew("ra", 3));
		tmp = tmp->next;
	}
	cut_tail(&comm, "ra");
	improve_comm_dub(&comm);
	tmp = comm;
	comm = NULL;
	fl = 0;
	while (tmp)
	{
		do_one_chaos_comm(a, b, tmp);
		add_comm(&comm, ft_lstnew(CCONT(tmp), 3));
		tmp = tmp->next;
	}
	return (comm);
}

int		push_a(int *standing, t_list **a, t_list **b, t_list **comm)
{
	int		i;
	int		count;
	t_list	*tmp;
	t_list	*new_comm;
	int		ret;

	new_comm = NULL;
	count = ft_lstlen(*b);
	i = -1;
	tmp = *b;
	ret = 0;
	while (++i < count)
	{
		if (standing[i] == 0 && (ret = ret + 1))
			ft_lstadd_back(&new_comm, ft_lstnew("pa", 3));
		else if (standing[i] == -1)
		{
			ft_lstadd_back(&new_comm, ft_lstnew("rrb", 4));
			ft_lstadd_back(&new_comm, ft_lstnew("sb", 3));
			ft_lstadd_back(&new_comm, ft_lstnew("rb", 3));
			ft_lstadd_back(&new_comm, ft_lstnew("rb", 3));
		}
		else
			ft_lstadd_back(&new_comm, ft_lstnew("rb", 3));
		tmp = tmp->next;
	}
	cut_tail(&new_comm, "rb");
	improve_comm_dub(&new_comm);
//	b++;
//	print_comm(new_comm);
	do_all_comm(a, b, new_comm, 0);
	add_comm(comm, new_comm);
	return (ret);
}
