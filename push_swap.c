/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 14:28:39 by mbartole          #+#    #+#             */
/*   Updated: 2019/04/05 05:03:23 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

static char	need_improve(t_list	*cur)
{
	if (cur && cur->next && cur->next->next &&
			(!ft_strcmp(CCONT(cur), "ra") &&
			  !ft_strcmp(CCONT(cur->next), "pa") &&
			  !ft_strcmp(CCONT(cur->next->next), "rra")))
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
		if (need_improve(cur->next))
		{
			tmp = cur->next;
			cur->next = cur->next->next;
			ft_lstdelone(&tmp, NULL);
			cur = cur->next;
			ft_memcpy(cur->cont, (void *)"sa", sizeof(char *));
		}
		cur = cur->next;
	}
}

/*
   static int	return_to_a(t_list **a, t_list **b, t_list *to_stand, t_list **comm, t_list **prev, int count)
   {
   t_list	*tmp;

   if (!(*b) || !to_stand)
   return(0);
   tmp = to_stand;
   while (tmp->next)
   tmp = tmp->next;
   printf("\n");
   print_stacks(to_stand, NULL);
   print_stacks(*a, *b);
   printf(" try to return %d between %d and %d ", ICONT(*b), ICONT(tmp), ICONT(to_stand));
   if ((ICONT(*b) < ICONT(to_stand) && ICONT(*b) > ICONT(tmp)) ||
   (ICONT(to_stand) < ICONT(tmp) &&
   ICONT(*b) > ICONT(to_stand) && ICONT(*b) < ICONT(tmp)))
   {
   printf(" - yes \n");
//		print_stacks(*a, *b);
//		print_comm(*comm);
tmp = ft_lstnew("pa", 3);
(*prev)->next = tmp;
tmp->next = *comm;
 *comm = tmp;
 one_comm_stacks(a, b, *comm);
 *prev = *comm;
 *comm = (*comm)->next;
 count++;

 if (!(return_to_a(a, b, *a, comm, prev, count)))
 {
 while (count--)
 {
 tmp = ft_lstnew("ra", 3);
 (*prev)->next = tmp;
 tmp->next = *comm;
 *comm = tmp;
 one_comm_stacks(a, b, *comm);
 *prev = *comm;
 i				*comm = (*comm)->next;
 }
//		print_stacks(*a, *b);
//		print_comm(*comm);
return (1);
}
//		printf("get   a: %d   b: %d   comm: %s \n",
//				ICONT(*a), ICONT(*b), CCONT(*comm));
}
printf(" - no \n");
return (0);
}*/
/*
   static void	rot_to_comm(int rot_a, int rot_b, t_list *comm)
   {
   int	i;

   if (rot_a > 0 && rot_b > 0)
   {
   while (rot_a && rot_b)
   {
   ft_lstadd_back(&comm, ft_lstnew("rr", 3));
   rot_a--;
   rot_b--;
   }
//		printf("rot a: %d rot b: %d\n", rot_a, rot_b);
i = rot_a ? rot_a : rot_b;
while (i-- > 0)
ft_lstadd_back(&comm, ft_lstnew(rot_a? "ra" : "rb", 3));
}
else if (rot_a < 0 && rot_b < 0)
{
while (rot_a && rot_b)
{
ft_lstadd_back(&comm, ft_lstnew("rrr", 4));
rot_a++;
rot_b++;
}
i = rot_a ? rot_a : rot_b;
while (i++ < 0)
ft_lstadd_back(&comm, ft_lstnew((rot_a ? "rra" : "rrb"), 4));
}
else
{
while (rot_a)
{
ft_lstadd_back(&comm, ft_lstnew((rot_a > 0 ? "ra" : "rra"), 3));
rot_a = rot_a > 0 ? rot_a - 1 : rot_a + 1;
}
while (rot_b)
{
ft_lstadd_back(&comm, ft_lstnew((rot_b > 0 ? "rb" : "rrb"), 3));
rot_b = rot_b > 0 ? rot_b - 1 : rot_b + 1;
}
}
}*/
/*
   static void	rotate_all(t_list **a, t_list **b, t_list *comm)
   {
   t_list	*tmp;
   int		rot_a;
   int		rot_b;
   int		len;
   int		max;

   tmp = *a;
   rot_a = 0;
   while (tmp && tmp->next)
   {
   if (ICONT(tmp) > ICONT(tmp->next))
   break ;
   rot_a++;
   tmp = tmp->next;
   }
   max = ICONT(tmp);
   len = ft_lstlen(*a);
   rot_a = rot_a < len / 2 ? rot_a : rot_a - len;
   tmp = *b;
   rot_b = 0;
   while (tmp && tmp->next)
   {
   if (ICONT(tmp) < ICONT(tmp->next))
   break ;
   rot_b++;
   tmp = tmp->next;
   }
   rot_b++;
   if (max < ICONT(tmp->next))
   rot_a++;
//	printf("rot a: %d rot b: %d\n", rot_a, rot_b);
len = ft_lstlen(*b);
if (rot_a > 0)
if (len - rot_b < rot_b - rot_a)
rot_b = rot_b - len;
if (rot_a < 0)
if (rot_b > len - rot_b + rot_a)
rot_b = rot_b - len;
rot_b = rot_b < len / 2 ? rot_b : rot_b - len;
//	printf("rot a: %d rot b: %d\n", rot_a, rot_b);
len = ft_lstlen(comm);
printf("len of comm: %d\n", len);
rot_to_comm(rot_a, rot_b, comm);
printf("len of comm: %d\n", ft_lstlen(comm));
while (len--)
comm = comm->next;
do_all_comm(a, b, comm);
}*/

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
	sorted = get_diff(in, 0, 0);
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
	int		tmp;

	i = 0;
	while (++i <= count)
	{
		ar = ft_strsplit(argv[i], ' ');
		while (*ar)
		{
			tmp = atoi_check(*ar);
			ft_lstadd_back(in, ft_lstnew((void *)&tmp, sizeof(int)));
			ar++;
		}
	}
	simplify(*in);
	return (ft_lstlen(*in));
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

	a = NULL;
	cp = lst_copy(b);
	comm = NULL;
//	print_stack(cp);
	choose_sequence(get_diff(cp, 1, 1), &standing, ft_lstlen(cp), 1);
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
	return (comm);
}

int			main(int argc, char **argv)
{
	t_list	*a;
	t_list	*b;
	//	t_list	*cp;
	int		*standing;
	int		len;
	//	int		i;
	t_list	*comm;
	t_list	*to_push;
	t_list	*new_comm;

	comm = NULL;
	if (argc < 2)
		return (clean("Error\n"));
	a = NULL;
	b = NULL;
	len = argv_to_list(&a, argv, argc - 1);
	choose_sequence(get_diff(a, 1, 0), &standing, len, 1);
//	improve_seq(a, standing);
	to_push = get_to_push(standing, a);
	push_b(standing, &a, &b, &comm);
	clever_push_b(comm, &a, &b, to_push);
	printf("first push to B:   ");//
	print_comm(comm);//
	while (ft_lstlen(b) > 5)
	{
	//	print_stacks(a, b);
		printf("A: %d	B: %d\n", ft_lstlen(a), ft_lstlen(b));
		choose_sequence(get_diff(b, 1, 0), &standing, ft_lstlen(b), 1);
	//	print_seq(standing, ft_lstlen(b));
	//	print_stack(b);
//		improve_seq(b, standing);
		new_comm = new_rot_all(&a, &b, standing, ft_lstlen(b));
	//	new_comm = rot_all(&a, &b, standing, ft_lstlen(b), 0);
		printf("cycle:   ");//
		print_comm(new_comm);//
		add_comm(&comm, new_comm);
		if (ft_lstlen(b) < len / 2 && ft_lstlen(last(b)) < 2 * len)
			break ;
	}

	new_comm = last(b);
	printf("INSERT (%d):   ", ft_lstlen(b));//
	print_comm(new_comm);//
	do_all_comm(&a, &b, new_comm, 0);
	add_comm(&comm, new_comm);
	choose_sequence(get_diff(b, 1, 1), &standing, ft_lstlen(b), 0);
//	improve_seq(b, standing);
	new_comm = rot_all(&a, &b, standing, ft_lstlen(b), 1);
	printf("final push to A:   ");//
	print_comm(new_comm);//
	add_comm(&comm, new_comm);
	new_comm = final_rotation(&a);
	printf("final rotation:   ");//
	print_comm(new_comm);//
	add_comm(&comm, new_comm);
	improve_comm(&comm);
	printf("FINAL:   ");//
	print_comm(comm);
//	print_stack(a);//
	return (0);
}
