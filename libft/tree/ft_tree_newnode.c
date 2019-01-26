/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treenew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 13:28:56 by mbartole          #+#    #+#             */
/*   Updated: 2019/01/26 13:40:49 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

t_avltree	*ft_tree_newnode(int key, void const *item, size_t item_s)
{
	t_avltree	*new;

	if (!(new = (t_avltree *)malloc(sizeof(t_avltree))))
		return (NULL);
	if (!(new->item = ft_memalloc(item_s)))
		return (NULL);
	if (item)
		ft_memcpy(new->item, item, item_s);
	new->key = key;
	new->item_s = item_s;
	new->left = NULL;
	new->right = NULL;
	new->h = 1;
	return (new);
}
