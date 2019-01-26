/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 13:39:08 by mbartole          #+#    #+#             */
/*   Updated: 2019/01/26 13:44:35 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_H
# define TREE_H

# include "../libft.h"

typedef struct	s_avltree
{
	int					key;
	void				*item;
	size_t				item_s;
	unsigned char		h;
	struct s_avltree	*left;
	struct s_avltree	*right;
}				t_avltree;

t_avltree		*ft_tree_newnode(int key, void const *item, size_t item_s);
t_avltree		*ft_tree_delnode(t_avltree *root, int key);
void			*ft_tree_search(t_avltree *root, int key);
void			ft_tree_putnode(void *node);
void			ft_tree_infix(t_avltree *root, void (*apply)(void *));
void			ft_tree_insert(t_avltree **r, int key, void const *item,
		size_t item_s);
void			ft_tree_balance(t_avltree **r);
void			ft_tree_print(t_avltree *tr, int digits);

#endif
