/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 18:13:11 by mbartole          #+#    #+#             */
/*   Updated: 2019/01/26 13:49:31 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

static t_vector	*add_nills(t_vector *v, int steps, int level)
{
	int	i;
	int	j;

	i = -1;
	while (++i < ft_power(2, steps - 1))
	{
		ft_vadd(v, "[", 1);
		j = -1;
		while (++j < (int)v->offset)
			ft_vadd(v, " ", 1);
		ft_vadd(v, "]", 1);
		j = -1;
		while (++j < (int)((ft_power(2, level) - 1) * (v->offset + 2)))
			ft_vadd(v, " ", 1);
	}
	return (v);
}

static t_vector	*add_node(t_vector *v, t_avltree *tr, int level)
{
	int		j;
	char	*num;

	ft_vadd(v, "[", 1);
	num = ft_itoa(tr->key);
	ft_vadd(v, num, ft_strlen(num));
	j = -1;
	while (++j < (int)v->offset - (int)ft_strlen(num))
		ft_vadd(v, " ", 1);
	free(num);
	ft_vadd(v, "]", 1);
	j = -1;
	while (++j < (int)((ft_power(2, level) - 1) * (v->offset + 2)))
		ft_vadd(v, " ", 1);
	return (v);
}

static t_vector	*get_level(t_vector *v, t_avltree *tr, int steps, int level)
{
	if (steps == 0)
		return (add_node(v, tr, level));
	if (tr->left)
		get_level(v, tr->left, steps - 1, level);
	else
		add_nills(v, steps, level);
	if (tr->right)
		get_level(v, tr->right, steps - 1, level);
	else
		add_nills(v, steps, level);
	return (v);
}

void			ft_tree_print(t_avltree *tr, int digits)
{
	int			i;
	int			j;
	t_vector	*lev;

	if (!tr)
		return ;
	i = -1;
	while (++i < tr->h)
	{
		ft_vnew(&lev, digits);
		lev->offset = digits;
		j = -1;
		while (++j < (int)((ft_power(2, tr->h - i - 2) - 1) * (digits + 2) +
				digits / 2 + 1))
			ft_vadd(lev, " ", 1);
		get_level(lev, tr, i, tr->h - i - 1);
		ft_putstr(lev->cont);
		ft_putstr("\n");
		ft_vreset(lev);
		free(lev);
	}
}
