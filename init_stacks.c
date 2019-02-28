/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 20:35:30 by mbartole          #+#    #+#             */
/*   Updated: 2019/02/28 15:38:25 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

static void	tree_to_lst(t_avltree *root, t_list **lst)
{
	if (root == NULL)
		return ;
	tree_to_lst(root->left, lst);
	ft_lstadd_back(lst, ft_lstnew((void *)&root->key, sizeof(int)));
	tree_to_lst(root->right, lst);
}

static void	lst_to_array(t_list *st, int *ar, int count)
{
	int	i;

	i = -1;
	while (st && ++i < count)
	{
		ar[i] = ICONT(st);
		st = st->next;
	}
}

static void init_razn(t_list **razn, int *sorted, t_list *in, int count)
{
	int	i;
	int	j;
	int	tmp;

	j = 0;
	while (in)
	{
		i = -1;
		while (++i < count)
			if (ICONT(in) == sorted[i])
			{
				ft_memcpy(in->cont, (void *)&i, sizeof(int));
				break ;
			}
		tmp = j - i;
		if (tmp < -count / 2)
			tmp += count;
		else if (tmp > count / 2)
			tmp -= count;
		ft_lstadd_back(razn, ft_lstnew((void *)&tmp, sizeof(int)));
		in = in->next;
		j++;
	}
}

int		*init_stacks(t_list *in, t_list **razn)
{
	t_avltree *tr;
	t_list	*tmpl;
	int		*sorted_ar;
	int		len;

	len = ft_lstlen(in);
	tr = NULL;
	tmpl = in;
	while (tmpl)	
	{
		ft_tree_insert(&tr, ICONT(tmpl), NULL, 0);
		tmpl = tmpl->next;
	}
	tmpl = NULL;
	tree_to_lst(tr, &tmpl);
	//TODO free tree
	sorted_ar = (int *)ft_memalloc(sizeof(int) * len);
	lst_to_array(tmpl, sorted_ar, len);
	ft_lstdel(&tmpl, NULL);
	init_razn(razn, sorted_ar, in, len);
	lst_to_array(*razn, sorted_ar, len);
	return (sorted_ar);
}
