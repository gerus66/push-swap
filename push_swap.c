/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 14:28:39 by mbartole          #+#    #+#             */
/*   Updated: 2019/04/10 02:19:14 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

static char	need_improve_a(t_list	*cur)
{
	if (cur && cur->next && cur->next->next &&
			(!ft_strcmp(CCONT(cur), "ra") &&
			  !ft_strcmp(CCONT(cur->next), "pa") &&
			  !ft_strcmp(CCONT(cur->next->next), "rra")))
		return (1);
	return (0);
}

static char	need_improve_b(t_list	*cur)
{
	if (cur && cur->next && cur->next->next &&
			(!ft_strcmp(CCONT(cur), "rb") &&
			  !ft_strcmp(CCONT(cur->next), "pb") &&
			  !ft_strcmp(CCONT(cur->next->next), "rrb")))
		return (1);
	return (0);
}

static void	improve_comm(t_list **comm)
{
	t_list	*tmp;
	t_list	*cur;

	cur = *comm;
	while (cur && cur->next && cur->next->next && cur->next->next->next)
	{
		if (need_improve_a(cur->next))
		{
			tmp = cur->next;
			cur->next = cur->next->next;
			ft_lstdelone(&tmp, NULL);
			cur = cur->next;
			ft_memcpy(cur->cont, (void *)"sa", sizeof(char *));
		}
		cur = cur->next;
	}
	cur = *comm;
	while (cur && cur->next && cur->next->next && cur->next->next->next)
	{
		if (need_improve_b(cur->next))
		{
			tmp = cur->next;
			cur->next = cur->next->next;
			ft_lstdelone(&tmp, NULL);
			cur = cur->next;
			ft_memcpy(cur->cont, (void *)"sb", sizeof(char *));
		}
		cur = cur->next;
	}
}

/*
static void		improve_seq(t_list *st, int *seq)
{
	int	len;
	int	i;
	int	j;
	int	prev;
	int	next;
	t_list	*cp;

	prev = 0;
	next = 0;
	len = ft_lstlen(st);
	i = -1;
	while (++i < len)
	{
		if (seq[i] == 1)
			prev = ICONT(st);
		if (seq[i] == 0 && ICONT(st) > prev && ICONT(st) < next)
			{
				seq[i] = 1;
				prev = ICONT(st);
				j = i;
				cp = st;
				while (++j < len)
				{
					if (seq[j] == 1 && seq[j + 1] == -1)
						next = ICONT(cp->next);
					else if (seq[i] == 1)
						next = ICONT(cp);
					cp = cp->next;
				}
			}
		st = st->next;
	}
}
*/
/*
static t_list   *to_push(t_list *st, int *seq)
{
	t_list  *push;
	int             i;
	t_list  *cp;
	int             len;

	push = NULL;
	len = ft_lstlen(st);
	cp = st;
	i = -1;
	while (++i < len)
	{
		if (seq[i] == 1)
			ft_lstadd_back(&push, ft_lstnew((void *)&ICONT(cp), sizeof(int)));
		else if (seq[i] == -1)
		{
			do_one_comm(&push, NULL, ft_lstnew("rra", 4));
			ft_lstadd_back(&push, ft_lstnew((void *)&ICONT(cp), sizeof(int)));
			do_one_comm(&push, NULL, ft_lstnew("ra", 4));
		}
		cp = cp->next;
	}
	//      print_stacks(st, push);
	return (push);
}
*/
/*
static void             improve_seq(t_list *st, int *seq)
{
	int     len;
	int     i;
	//	int     j;
	int     prev;
	int     last;
	//      int     next;
	t_list  *cp;
	t_list  *push;
	int     first;

	cp = st;
	push = to_push(st, seq);
	first = ICONT(push);
	len = ft_lstlen(st);
	last = last_elem(push);
	prev = ICONT(push);
	cp = push;
	while (cp->next && ICONT(cp->next) != last)
		cp = cp->next;
	prev = ICONT(cp);
	//      next = 0;
	i = -1;
	while (++i < len)
	{
//		printf("prev %d | last %d | next %d | cur %d\n", prev, last,
//				push ? ICONT(push) : first, ICONT(st));
		if (seq[i])
		{
			prev = last;
			last = ICONT(push);
			push = push->next;
		}
		else
		{
			if (ICONT(st) > prev && ICONT(st) < last)
			{
				printf("|%d|", ICONT(st));
				seq[i] = -1;
				prev = ICONT(st);
			}
			else if (ICONT(st) > last &&
					((push && ICONT(st) < ICONT(push)) ||
					 (!push && ICONT(st) < first)))
			{
				printf("/%d/", ICONT(st));
				seq[i] = 1;
				prev = last;
				last = ICONT(st);
			}
			//                      else if (push && ICONT(st) > ICONT(push) &&
			//						((push->next && ICONT(st) < ICONT(push->next)) ||
			//						(!(push->next) && ICONT(st) < first)))
			//						{
			//						printf("-/%d/-", ICONT(st));
			//						seq[i] = 1;
			//						prev = last;
			//						last = ICONT(st);
			//						}
		}
//		st = st->next;
//	}
	//      if (!in_prev && !in_last)
	//              improve_seq(cp, seq, prev, last);
}
*/
static void	simplify(t_list *in)
{
	int	*sorted;
	int	i;
	int	count;

	count = ft_lstlen(in);
	sorted = get_diff(in, 0, 0, ft_lstlen(in));
	while (in)
	{
		i = -1;
		while (++i < count)
			if (ICONT(in) == sorted[i])
			{
				ft_memcpy(in->cont, (void *)&i, sizeof(int));
				break ;
			}
		in = in->next;
	}
}

/*
   static t_list	*bubble(t_list *st)
   { 
   int	i;
   int	len;
   int	max;
   char	fl;
   t_list	*comm;
   t_list	*cp;

   comm = NULL;
   len = ft_lstlen(st);
   if (len < 3)
   return (NULL);
   cp = lst_copy(st);
   simplify(cp);
//	print_stack(cp);
max = len - 1;
fl = 1;
while (fl)
{
fl = 0;
i = -1;
while (++i < len)
{
if (ICONT(cp) > ICONT(cp->next) && ICONT(cp) != max)
{
add_and_do(&comm, NULL, &cp, "sb");
fl = 1;
}
add_and_do(&comm, NULL, &cp, "rb");
}
i = cut_tail(&comm, "rb");
while (--i >= 0)
do_one_comm(NULL, &cp, ft_lstnew("rrb", 4));
//		while (ICONT(cp) < ICONT(cp->next))
//			add_and_do(&comm, NULL, &cp, "rrb");
//	add_and_do(&comm, NULL, &cp, "rb");
}
//	print_stack(cp);//
//	cut_tail(&comm, "rb");
//	print_comm(comm);
return (comm);
}*/

static int	argv_to_list(t_list **in, char **argv, int count)
{
	int		i;
	char	**ar;
	char	**cp;
	int		tmp;
	int		len;

	i = 0;
	len = 0;
	while (++i <= count)
	{
		ar = ft_strsplit(argv[i], ' ');
		cp = ar;
		while (*ar)
		{
			tmp = atoi_check(*ar);
			free(*ar);
			ft_lstadd_back(in, ft_lstnew((void *)&tmp, sizeof(int)));
			len++;
			ar++;
		}
		free(cp);
	}
	simplify(*in);
	return (len);
}

/*
 ** rotate sorted stack to the start [ < N / 2]
 */

static t_list	*final_rotation(t_list **st)
{
	t_list	*comm;
	int		len;

	comm = NULL;
	len = ft_lstlen(*st);
	if (len - ICONT(*st) < len / 2)
		while (ICONT(*st) != 0)
			add_and_do(&comm, st, NULL, "ra");
	else
		while (ICONT(*st) != 0)
			add_and_do(&comm, st, NULL, "rra");
	return (comm);
}

static t_list	*last(t_list *b)
{
	t_list	*comm;
	t_list	*a;
	t_list	*cp;
	int		*standing;
	int		i;

	printf("last --->\n");
	a = NULL;
	cp = lst_copy(b);
	comm = NULL;
//	print_stack(cp);
	choose_sequence(get_diff(cp, 1, 1, ft_lstlen(cp)), &standing, ft_lstlen(cp), 1);
//	print_seq(standing, ft_lstlen(cp));
	i = push_a(standing, &a, &cp, &comm);
//	print_stacks(a, b);
	//	printf(">> %d %d\n", i, ft_lstlen(a));
	while (--i >= 0)
	{
//		if ()
		add_comm(&comm, push_one_last(&a, &cp, &i));
	}
//	printf("TRY INSERT (%d) - %d\n", ft_lstlen(b), ft_lstlen(comm));//
	printf("--->last\n");
	return (comm);
}

static void		add_seq(int **seq, int count, int len)
{
	int	*new;

	if (count >= len)
		return ;
	new = (int *)ft_memalloc(sizeof(int) * len);
	ft_memcpy(new, *seq, sizeof(int) * count);
	*seq = new;
}

int			main(int argc, char **argv)
{
	t_list	*a;
	t_list	*b;
	//	t_list	*cp;
	int		*standing;
	int		len;
	int		subseq;
	t_list	*comm;
//	t_list	*to_push;
	t_list	*new_comm;

//	comm = NULL;
	if (argc < 2)
		return (clean("Error\n"));
	a = NULL;
	b = NULL;
	len = argv_to_list(&a, argv, argc - 1);
//	print_stack(a);
	choose_sequence(get_diff(a, 1, 0, ft_lstlen(a)), &standing, len, 1);
//	improve_seq(a, standing);
//	to_push = get_to_push(standing, a);
	comm = push_b(standing, &a, &b);
//	clever_push_b(comm, &a, &b, to_push);
	printf("first push to B:   ");//
	print_comm(comm);//
	while (ft_lstlen(b) > 5)
	{
		printf("A: %d	B: %d\n", ft_lstlen(a), ft_lstlen(b));//
		new_comm = back_to_a(&a, &b);
		printf("cycle:   ");//
		print_comm(new_comm);//
		add_comm(&comm, new_comm);
		if (ft_lstlen(last(b)) < len)
			break ;
	}
	new_comm = last(b);
	printf("INSERT (%d):   ", ft_lstlen(b));//
	print_comm(new_comm);//
	do_all_comm(&a, &b, new_comm, 0);
	add_comm(&comm, new_comm);
//	print_stacks(a, b);
	new_comm = back_to_a_last(&a, &b);
	printf("final push to A:   ");//
	print_comm(new_comm);//
	add_comm(&comm, new_comm);
	new_comm = final_rotation(&a);
	printf("final rotation:   ");//
	print_comm(new_comm);//
	add_comm(&comm, new_comm);
	improve_comm(&comm);
	improve_comm_dub(&comm);
	printf("FINAL:   ");//
	print_comm(comm);
//	print_stack(a);//
	return (0);
}
