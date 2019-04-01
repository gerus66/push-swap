/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 14:21:02 by mbartole          #+#    #+#             */
/*   Updated: 2019/04/01 21:44:26 by mbartole         ###   ########.fr       */
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

int		*get_diff(t_list *in, char fl);

/*
** choose sorted sequence
*/

void	choose_sequence(int *razn, int **standing, int count, char fl);

/*
** push to B (one time, the first)
*/

void	push_b(int *standing, t_list **a, t_list **b, t_list **comm);
void	clever_push_b(t_list *comm, t_list **a, t_list **b, t_list *to_push);

/*
** push to A (in cycle)
*/

t_list  *get_to_push(int *seq, t_list *st);
t_list  *rot_all(t_list **a, t_list **b, int *seq, int count);
void    push_a(t_list **a, t_list **b, t_list *comm);
t_list  *adjust_stacks(t_list **a, t_list **b, int *seq, int count);

void    print_comm(t_list *comm);
void	print_stacks(t_list *a, t_list *b);
void	print_stack(t_list *a);
int     last_elem(t_list *stack);
void    do_one_comm(t_list **a, t_list **b, t_list *comm);
void    do_one_chaos_comm(t_list **a, t_list **b, t_list *comm);
void    do_all_comm(t_list **a, t_list **b, t_list *comm, char chaos);
void        add_comm(t_list **comm, t_list *add);
void    add_and_do(t_list **comm, t_list **a, t_list **b, char *name);
void    cut_tail(t_list **comm, char *name);
char    can_insert(int val, t_list *st);


//void    lst_to_array(t_list *st, int *ar, int count);
int     atoi_check(char *s);
int		clean(char *msg);
t_list	*atoi_stack(t_list *stack);

#endif
