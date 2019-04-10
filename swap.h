/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 14:21:02 by mbartole          #+#    #+#             */
/*   Updated: 2019/04/10 02:35:17 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

# include "libft/libft.h"

# include <stdio.h> //TODO

#define I_MAX 2147483647
#define I_MIN -2147483648

# define ERR_M "Error\n"

# define ICONT(x) (*((int *)(x)->cont))
# define CCONT(x) ((char *)(x)->cont)

# define MAX(x, y) ((x) > (y) ? (x) : (y))
# define MIN(x, y) ((x) < (y) ? (x) : (y))
# define ABS(x) ((x) < 0 ? -(x) : (x))

/*
** operations with stack
*/

void	swap_stack(t_list **st);
void	push_stack(t_list **src, t_list **dst);
void	rotate_stack(t_list **st);
void	r_rotate_stack(t_list **st);

/*
** get sequence of diffs for current stack
*/

int		*get_diff(t_list *in, char fl, char reverse, int number);

/*
** choose sorted sequence
*/

void	choose_sequence(int *razn, int **standing, int count, char fl);

/*
** push to B (one time, the first)
*/

t_list	*push_b(int *standing, t_list **a, t_list **b);
int		push_a(int *standing, t_list **a, t_list **b, t_list **comm);
//void	clever_push_b(t_list *comm, t_list **a, t_list **b, t_list *to_push);
void    improve_comm_dub(t_list **comm);

/*
** push back to A (in cycle)
*/

t_list		*back_to_a(t_list **a, t_list **b);
int			get_rot(t_list *st, int to_push, int i, int len_b, char *fl);
t_list		*perform_rot(t_list **a, t_list **b, int to_push, char fl);
//t_list		*push_one_last(t_list **a, t_list **b, int *i);

/*
** push back to A reversed sorted B
*/

t_list  *back_to_a_last(t_list **a, t_list **b);

/*
** sort remains in B
*/

t_list		*last(t_list *b);


//t_list  *adjust_stacks_last(t_list **a, t_list **b, int *seq, int count, char fl);

t_list  *get_to_push(int *seq, t_list *st);
//t_list  *push_one_ba(t_list **a, t_list **b);

void    print_seq(int *seq, int count);
void    print_comm(t_list *comm);
void	print_stacks(t_list *a, t_list *b);
void	print_stack(t_list *a);
int     last_elem(t_list *stack);
int     prelast_elem(t_list *stack);
void    do_one_comm(t_list **a, t_list **b, t_list *comm);
void    do_one_chaos_comm(t_list **a, t_list **b, t_list *comm);
void    do_all_comm(t_list **a, t_list **b, t_list *comm, char chaos);
void        add_comm(t_list **comm, t_list *add);
void    add_and_do(t_list **comm, t_list **a, t_list **b, char *name);
int	    cut_tail(t_list **comm, char *name);
char	can_insert(int val, int first, int last);
char	can_insert_rev(int val, t_list *st);
t_list	*lst_copy(t_list *lst);

//void    lst_to_array(t_list *st, int *ar, int count);
int     atoi_check(char *s);
int		clean(char *msg);
t_list	*atoi_stack(t_list *stack);

#endif
