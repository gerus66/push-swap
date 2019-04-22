/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_argv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 04:26:20 by mbartole          #+#    #+#             */
/*   Updated: 2019/04/22 17:55:25 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

static int		atoi_check(char *s, t_stacks *all)
{
	ssize_t	res;
	char	sign;

	res = 0;
	sign = (*s == '-' ? -1 : 1);
	if (*s == '-' || *s == '+')
		s++;
	while (*s)
	{
		if (*s >= '0' && *s <= '9')
			res = res * 10 + *s - 48;
		else
			exit(clean(ERR_M, all));
		s++;
	}
	res *= sign;
	if (res > I_MAX || res < I_MIN)
		exit(clean(ERR_M, all));
	return ((int)res);
}

static void		double_check(int val, t_stacks *all)
{
	t_list	*cp;

	cp = all->a;
	while (cp)
	{
		if (ICONT(cp) == val)
			exit(clean(ERR_M, all));
		cp = cp->next;
	}
}

void			simplify(t_list *in, int count)
{
	int	sorted[count];
	int	i;

	get_diff(in, sorted, 0, 0);
	while (in)
	{
		i = -1;
		while (++i < count)
			if (ICONT(in) == sorted[i])
			{
				ft_memcpy(in->cont, (void *)&i, sizeof(int));
				break ;
			}
		in = in->next;
	}
}

static void		read_argv(t_stacks *all, char **argv, int count)
{
	int		i;
	int		tmp;
	t_list	*new;
	char	**ar;
	char	**cp;

	i = 0;
	while (++i <= count)
	{
		if (!(ar = ft_strsplit(argv[i], ' ')))
			exit(clean(ERM_M, all));
		cp = ar;
		while (*ar)
		{
			tmp = atoi_check(*ar, all);
			free(*ar);
			double_check(tmp, all);
			if (!(new = ft_lstnew((void *)&tmp, sizeof(int))))
				exit(clean(ERM_M, all));
			ft_lstadd_back(&all->a, new);
			all->len_a++;
			ar++;
		}
		free(cp);
	}
}

void			init_all(t_stacks *all, char **argv, int count, char simple)
{
	all->a = NULL;
	all->b = NULL;
	all->comm = NULL;
	all->local_comm = NULL;
	all->len_a = 0;
	all->len_b = 0;
	read_argv(all, argv, count);
	if (!all->len_a)
		exit(clean(ERR_M, all));
	if (simple)
		simplify(all->a, ft_lstlen(all->a));
}
