/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_argv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 04:26:20 by mbartole          #+#    #+#             */
/*   Updated: 2019/04/11 01:17:59 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

static int		atoi_check(char *s, t_list *lst)
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
			exit(clean(ERR_M, &lst, 1));
		s++;
	}
	res *= sign;
	if (res > I_MAX || res < I_MIN)
		exit(clean(ERR_M, &lst, 1));
	return ((int)res);
}

static void		double_check(int val, t_list *in)
{
	t_list	*cp;

	cp = in;
	while (cp)
	{
		if (ICONT(cp) == val)
			exit(clean(ERR_M, &in, 1));
		cp = cp->next;
	}
}

static void		simplify(t_list *in)
{
	int	*sorted;
	int	i;
	int	count;

	count = ft_lstlen(in);
	sorted = get_diff(in, 0, 0, count);
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
	free(sorted);
}

int				argv_to_list(t_list **in, char **argv, int count, char simple)
{
	int		i;
	char	**ar;
	char	**cp;
	int		tmp;
	int		len;

	len = 0;
	i = 0;
	while (++i <= count)
	{
		ar = ft_strsplit(argv[i], ' ');
		cp = ar;
		while (*ar && ++len)
		{
			tmp = atoi_check(*ar, *in);
			free(*ar);
			double_check(tmp, *in);
			ft_lstadd_back(in, ft_lstnew((void *)&tmp, sizeof(int)));
			ar++;
		}
		free(cp);
	}
	if (simple)
		simplify(*in);
	return (len);
}
