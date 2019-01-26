/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_create_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 01:40:46 by mbartole          #+#    #+#             */
/*   Updated: 2019/01/26 13:50:34 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

void	*ft_tree_search(t_avltree *root, int key)
{
	if (!root)
		return (NULL);
	if (key == root->key)
		return (root->item);
	else if (key < root->key)
		return (ft_tree_search(root->left, key));
	else
		return (ft_tree_search(root->right, key));
}
