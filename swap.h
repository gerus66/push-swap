/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 14:21:02 by mbartole          #+#    #+#             */
/*   Updated: 2019/02/04 10:25:54 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

# include "libft/libft.h"

# include <stdio.h> //TODO

# define ERR_M "Error\n"

# define ICONT(x) (*((int *)(x)->cont))

void	swap_stack(t_list **st);
void	push_stack(t_list **src, t_list **dst);
void	rotate_stack(t_list **st);
void	r_rotate_stack(t_list **st);
t_list	*atoi_stack(t_list *stack);

void	print_stacks(t_list *a, t_list *b);

#endif
