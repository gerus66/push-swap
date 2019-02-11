/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 14:21:02 by mbartole          #+#    #+#             */
/*   Updated: 2019/02/11 15:24:39 by mbartole         ###   ########.fr       */
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

void	swap_stack(t_list **st);
void	push_stack(t_list **src, t_list **dst);
void	rotate_stack(t_list **st);
void	r_rotate_stack(t_list **st);
t_list	*atoi_stack(t_list *stack);

void	print_stacks(t_list *a, t_list *b);

void    comm_stacks(t_list **a, t_list **b, t_list *comm);

void    lst_to_array(t_list *st, int *ar, int count);
void    tree_to_lst(t_avltree *root, t_list **lst);
int     atoi_check(char *s);
int		clean(char *msg);

#endif