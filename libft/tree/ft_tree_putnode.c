/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree_putnode.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 12:20:17 by mbartole          #+#    #+#             */
/*   Updated: 2019/01/26 13:50:11 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

void	ft_tree_putnode(void *node)
{
	if (((t_avltree *)node)->left)
		ft_putstr(" <--");
	ft_putstr("[");
	ft_putnbr((int)((t_avltree *)node)->key);
	ft_putstr("]");
	ft_putstr("[h = ");
	ft_putnbr((char)((t_avltree *)node)->h);
	ft_putstr("]");
	if (((t_avltree *)node)->right)
		ft_putstr("-->");
	ft_putstr("\n");
}
