/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 14:21:02 by mbartole          #+#    #+#             */
/*   Updated: 2019/02/27 12:58:22 by mbartole         ###   ########.fr       */
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
** operators on stack
*/

void	swap_stack(t_list **st);
void	push_stack(t_list **src, t_list **dst);
void	rotate_stack(t_list **st);
void	r_rotate_stack(t_list **st);

/*
** common for swap and checker functions
*/
int		argv_to_list(t_list **in, char **argv, int count);
void    do_one_comm(t_list **a, t_list **b, t_list *comm);
void    do_all_comm(t_list **a, t_list **b, t_list *comm);

/*
** utils for push_swap
*/

//void    lst_to_array(t_list *st, int *ar, int count);
void    print_comm(t_list *comm);
int     last_elem(t_list *stack);
void    do_push(t_list **a, t_list **b, t_list *comm);
void    do_all_push(t_list **a, t_list **b, t_list *comm);

/*
** utils for checker
*/

//t_list	*atoi_stack(t_list *stack);//TODO
void	print_stacks(t_list *a, t_list *b);

/*
** choose magic sequence
*/

//void        choose_sequence(int *razn, int **standing, int count, char fl);
void    choose_sequence(int count, t_list *stack, int **standing);

t_list  *push_to_b(int *standing, t_list **a, t_list **b, int count);

//void    tree_to_lst(t_avltree *root, t_list **lst);
//int     atoi_check(char *s);
//int		clean(char *msg);

#endif
