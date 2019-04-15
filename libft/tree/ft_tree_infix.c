/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_create_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 01:40:46 by mbartole          #+#    #+#             */
/*   Updated: 2019/01/26 13:47:14 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

void	ft_tree_infix(t_avltree *root, void (*applyf)(void *))
{
	if (root == NULL)
		return ;
	ft_tree_infix(root->left, applyf);
	applyf(root);
	ft_tree_infix(root->right, applyf);
}
