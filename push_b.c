/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_to_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 08:07:46 by mbartole          #+#    #+#             */
/*   Updated: 2019/03/12 18:48:36 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

static void	delete_ra(t_list **comm)
{
	t_list	*tmp;
	t_list	*del;

	if (!(*comm))
		return ;
	tmp = *comm;
	while (tmp->next && tmp->next->next)
		tmp = tmp->next;
	if (ft_strcmp(CCONT(tmp->next), "ra"))
		return ;
	del = tmp->next;
	tmp->next = NULL;
	ft_lstdelone(&del, NULL);
	delete_ra(comm);
}

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

static void	improve_comm(t_list **comm)
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
		improve_comm(comm);
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

#define PARTS 10
#define FIRST_SORT 20
#define FL_SORT_ALL 0
#define FL_SORT_PARTS 1
#define FL_NO_SORT 66

static int	get_rot_b(t_list *to_push, t_list *b, int n, char fl)
{
	int rot;
	int	len;

	n = n / PARTS;
	len = ft_lstlen(b);
	if (len < 2 || !to_push || fl == FL_NO_SORT)
		return (0);
	rot = 1;
	while (b && b->next)
	{
	//	printf("%d from %d to %d\n", ICONT(to_push), n * (ICONT(to_push) / n), n * (ICONT(to_push) / n + 1));
		if ((ICONT(b) < ICONT(to_push) && ICONT(to_push) < ICONT(b->next)) ||
				(ICONT(b) > ICONT(b->next) && ICONT(to_push) < ICONT(b->next)) ||
				(ICONT(b) > ICONT(b->next) && ICONT(to_push) > ICONT(b)))
			break ;
		else if (fl && len > FIRST_SORT && 
				 (ICONT(b) > n * (ICONT(to_push) / n) && ICONT(b) < n * (ICONT(to_push) / n + 1)))
			break ;
	//	else
	//		printf("_");
		b = b->next;
		rot++;
	}
	if (!(b->next))
		return (0);
	return (rot <= len / 2 ? rot : rot - len);
}

void	clever_push_b(t_list *comm, t_list **a, t_list **b, t_list *to_push)
{
	int	rot_b;
	t_list	*tmp;
	t_list	*prev;

	prev = comm;
	while (comm)
	{
		rot_b = get_rot_b(to_push, *b, ft_lstlen(*a), 66);
//		printf("ROT B = %d\n", rot_b);
		if (rot_b > 0 && !ft_strcmp(CCONT(comm), "ra"))
		{
			ft_memcpy(comm->cont, (void *)"rr", sizeof(char *));
			rot_b--;
		}
		else if (rot_b < 0 && !ft_strcmp(CCONT(comm), "rra"))
		{
			ft_memcpy(comm->cont, (void *)"rrr", sizeof(char *));
			rot_b++;
		}
		if (!ft_strcmp(CCONT(comm), "pb"))
		{
			to_push = to_push->next;
			while (rot_b)
			{
				tmp = rot_b > 0 ? ft_lstnew("rb", 3) : ft_lstnew("rrb", 4);
				prev->next = tmp;
				tmp->next = comm;
				comm = tmp;
				rot_b = rot_b > 0 ? rot_b - 1 : rot_b + 1;
				do_one_comm(a, b, comm);
				prev = comm;
				comm = comm->next;
			}
		}
		do_one_chaos_comm(a, b, comm);
		prev = comm;
		comm = comm->next;
	}
//	delete_ra(&comm);
//	improve_comm(&comm);
//	do_push(a, b, comm);
}

t_list	*push_b(int *standing, t_list **a, t_list **b, t_list **comm)
{
	int		i;
	int		count;
	t_list	*to_push;
	t_list	*tmp;

	count = ft_lstlen(*a);
	to_push = NULL;
	i = -1;
	tmp = *a;
	while (++i < count)
	{
		if (standing[i] == 0)
		{
			ft_lstadd_back(comm, ft_lstnew("pb", 3));
			ft_lstadd_back(&to_push,ft_lstnew(tmp->cont, sizeof(int)));
		}
		else if (standing[i] == -1)
		{
			ft_lstadd_back(comm, ft_lstnew("rra", 4));
			ft_lstadd_back(comm, ft_lstnew("sa", 3));
			ft_lstadd_back(comm, ft_lstnew("ra", 3));
			ft_lstadd_back(comm, ft_lstnew("ra", 3));
		}
		else
			ft_lstadd_back(comm, ft_lstnew("ra", 3));
		tmp = tmp->next;
	}
	delete_ra(comm);
	improve_comm(comm);
	b++;
//	do_push(a, b, *comm);
	return (to_push);
	//	do_all_comm(a, b, *comm);
}
