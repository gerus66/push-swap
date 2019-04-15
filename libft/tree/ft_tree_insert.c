/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_create_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 01:40:46 by mbartole          #+#    #+#             */
/*   Updated: 2019/01/26 13:47:42 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

void	ft_tree_insert(t_avltree **r, int key, void const *item, size_t item_s)
{
	if (!r)
		return ;
	if (!*r)
		*r = ft_tree_newnode(key, item, item_s);
	else if (key < (*r)->key)
		ft_tree_insert(&(*r)->left, key, item, item_s);
	else
		ft_tree_insert(&(*r)->right, key, item, item_s);
	ft_tree_balance(r);
}
