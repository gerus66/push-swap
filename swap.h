/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 14:21:02 by mbartole          #+#    #+#             */
/*   Updated: 2019/02/28 17:22:28 by mbartole         ###   ########.fr       */
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

int		*get_diff(t_list *in);

/*
** choose sorted sequence
*/

void	choose_sequence(int *razn, int **standing, int count, char fl);

/*
** push to b (one time, the first)
*/

t_list	*push_b(int *standing, t_list *a, t_list **comm, int count);


void	print_stacks(t_list *a, t_list *b);

void    comm_stacks(t_list **a, t_list **b, t_list *comm);
void    one_comm_stacks(t_list **a, t_list **b, t_list *comm);

//void    lst_to_array(t_list *st, int *ar, int count);
int     atoi_check(char *s);
int		clean(char *msg);
t_list	*atoi_stack(t_list *stack);

#endif
