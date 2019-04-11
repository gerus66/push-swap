/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 20:35:30 by mbartole          #+#    #+#             */
/*   Updated: 2019/04/11 03:57:50 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

static void		tree_to_lst(t_avltree *root, t_list **lst)
{
	if (root == NULL)
		return ;
	tree_to_lst(root->left, lst);
	ft_lstadd_back(lst, ft_lstnew((void *)&root->key, sizeof(int)));
	tree_to_lst(root->right, lst);
	free(root);
}

static void		lst_to_array(t_list *st, int *ar, int count)
{
	int	i;

	i = -1;
	while (st && ++i < count)
	{
		ar[i] = ICONT(st);
		st = st->next;
	}
}

static void		reverse_it(int *sorted_ar, int len)
{
	int	i;
	int	tmp;

	i = -1;
	while (++i < len / 2)
	{
		tmp = sorted_ar[i];
		sorted_ar[i] = sorted_ar[len - i - 1];
		sorted_ar[len - i - 1] = tmp;
	}
}

static void		init_razn(int *sorted, t_list *in, int count)
{
	int	i;
	int	j;
	int	tmp;
	int	*razn;

	razn = (int *)ft_memalloc(sizeof(int) * count);
	j = -1;
	while (in)
	{
		i = -1;
		while (++i < count)
			if (ICONT(in) == sorted[i])
				break ;
		tmp = ++j - i;
		if (tmp < -count / 2)
			tmp += count;
		else if (tmp > count / 2)
			tmp -= count;
		razn[j] = tmp;
		in = in->next;
	}
	i = -1;
	while (++i < count)
		sorted[i] = razn[i];
	free(razn);
}

void			get_diff(t_list *in, int *sorted_ar, char razn, char reverse)
{
	t_avltree	*tr;
	t_list		*cp;
	int			len;

	tr = NULL;
	cp = in;
	while (cp)
	{
		ft_tree_insert(&tr, ICONT(cp), NULL, 0);
		cp = cp->next;
	}
	cp = NULL;
	tree_to_lst(tr, &cp);
	len = ft_lstlen(in);
	lst_to_array(cp, sorted_ar, len);
	ft_lstdel(&cp, NULL);
	if (reverse)
		reverse_it(sorted_ar, len);
	if (razn)
		init_razn(sorted_ar, in, len);
}
