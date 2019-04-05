/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 20:35:30 by mbartole          #+#    #+#             */
/*   Updated: 2019/04/05 00:23:51 by mbartole         ###   ########.fr       */
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

static int	*init_razn(int *sorted, t_list *in, int count)
{
	int	i;
	int	j;
	int	tmp;
	int	*razn;


	razn = (int *)ft_memalloc(sizeof(int) * count);
	j = 0;
	while (in)
	{
		i = -1;
		while (++i < count)
			if (ICONT(in) == sorted[i])
				break ;
		tmp = j - i;
		if (tmp < -count / 2)
			tmp += count;
		else if (tmp > count / 2)
			tmp -= count;
		razn[j] = tmp;
		in = in->next;
		j++;
	}
	free(sorted);
	return (razn);
}

int		*get_diff(t_list *in, char fl, char reverse)
{
	t_avltree *tr;
	t_list	*cp;
	int		*sorted_ar;
	int		len;

	len = ft_lstlen(in);
	tr = NULL;
	cp = in;
	while (cp)	
	{
		ft_tree_insert(&tr, ICONT(cp), NULL, 0);
		cp = cp->next;
	}
	cp = NULL;
	tree_to_lst(tr, &cp);
	//TODO free tree
	sorted_ar = (int *)malloc(sizeof(int) * len);
	lst_to_array(cp, sorted_ar, len);
	ft_lstdel(&cp, NULL);
//	print_seq(sorted_ar, len);
	if (reverse)
	{
		int i = -1;
		int	tmp;
		while (++i < len / 2)
		{
			tmp = sorted_ar[i];
			sorted_ar[i] = sorted_ar[len - i - 1];
			sorted_ar[len - i - 1] = tmp;
		}
	}
//	print_seq(sorted_ar, len);
	if (fl)
		return (init_razn(sorted_ar, in, len));
	else
		return(sorted_ar);
}
