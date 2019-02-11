/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree_balance.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 11:35:42 by mbartole          #+#    #+#             */
/*   Updated: 2019/02/07 17:00:10 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

static int	recalc_h(t_avltree *r)
{
	int	hr;
	int	hl;

	hr = (r->right ? r->right->h : 0);
	hl = (r->left ? r->left->h : 0);
	r->h = (hr > hl ? hr : hl) + 1;
	return (hr - hl);
}

static void	rot_left(t_avltree **r)
{
	t_avltree	*tmp;

	tmp = (*r)->right;
	(*r)->right = tmp->left;
	tmp->left = *r;
	*r = tmp;
	recalc_h((*r)->left);
	recalc_h(*r);
}

static void	rot_right(t_avltree **r)
{
	t_avltree	*tmp;

	tmp = (*r)->left;
	(*r)->left = tmp->right;
	tmp->right = *r;
	*r = tmp;
	recalc_h((*r)->right);
	recalc_h(*r);
}

void		ft_tree_balance(t_avltree **r)
{
	if (!r || !*r)
		return ;
	if (recalc_h(*r) == 2)
	{
		if (recalc_h((*r)->right) < 0)
			rot_right(&((*r)->right));
		rot_left(r);
	}
	else if (recalc_h(*r) == -2)
	{
		if (recalc_h((*r)->left) > 0)
			rot_left(&((*r)->left));
		rot_right(r);
	}
}
