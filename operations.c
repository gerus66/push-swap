/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_comm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 18:51:58 by mbartole          #+#    #+#             */
/*   Updated: 2019/02/25 20:06:39 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

#define I_MAX 2147483647
#define I_MIN -2147483648

void	swap_stack(t_list **st)
{
	t_list	*tmp;

	if (!(*st) || !(*st)->next)
		return ;
	tmp = (*st)->next;
	(*st)->next = (*st)->next->next;
	tmp->next = *st;
	*st = tmp;
}

void	push_stack(t_list **src, t_list **dst)
{
	t_list	*tmp;

	if (!(*src))
		return ;
	tmp = (*src)->next;
	(*src)->next = (*dst);
	*dst = *src;
	*src = tmp;
}

void	rotate_stack(t_list **st)
{
	t_list	*tmp;

	if (!(*st) || !(*st)->next)
		return ;
	tmp = *st;
	while ((*st)->next)
		*st = (*st)->next;
	(*st)->next = tmp;
	*st = tmp->next;
	tmp->next = NULL;
}

void	r_rotate_stack(t_list **st)
{
	t_list	*tmp;

	if (!(*st) || !(*st)->next)
		return ;
	tmp = *st;
	while ((*st)->next->next)
		*st = (*st)->next;
	(*st)->next->next = tmp;
	tmp = (*st)->next;
	(*st)->next = NULL;
	*st = tmp;
}