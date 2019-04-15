/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree_delnode.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 13:10:00 by mbartole          #+#    #+#             */
/*   Updated: 2019/01/26 13:41:30 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

static t_avltree	*extract_min(t_avltree *root)
{
	if (!root->left)
		return (root->right);
	root->left = extract_min(root->left);
	ft_tree_balance(&root);
	return (root);
}

static t_avltree	*find_min(t_avltree *root)
{
	return (root->left ? find_min(root->left) : root);
}

t_avltree			*ft_tree_delnode(t_avltree *root, int key)
{
	t_avltree	*min;

	if (!root)
		return (NULL);
	if (key < root->key)
		root->left = ft_tree_delnode(root->left, key);
	else if (key > root->key)
		root->right = ft_tree_delnode(root->right, key);
	else
	{
		if (!root->right)
			min = root->left;
		else
		{
			min = find_min(root->right);
			root->right = extract_min(root->right);
			min->left = root->left;
			min->right = root->right;
		}
		free(root->item);
		free(root);
		root = min;
	}
	ft_tree_balance(&root);
	return (root);
}
