/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_argv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 04:26:20 by mbartole          #+#    #+#             */
/*   Updated: 2019/04/10 04:41:24 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

static int		atoi_check(char *s)
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
			exit(clean(ERR_M));//TODO
		s++;
	}
	res *= sign;
	if (res > I_MAX || res < I_MIN)
		exit(clean(ERR_M));//TODO
	return ((int)res);
}

static void	simplify(t_list *in)
{
	int	*sorted;
	int	i;
	int	count;

	count = ft_lstlen(in);
	sorted = get_diff(in, 0, 0, ft_lstlen(in));
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

int	argv_to_list(t_list **in, char **argv, int count, char simple)
{
	int		i;
	char	**ar;
	char	**cp;
	int		tmp;
	int		len;

	i = 0;
	len = 0;
	while (++i <= count)
	{
		ar = ft_strsplit(argv[i], ' ');
		cp = ar;
		while (*ar)
		{
			tmp = atoi_check(*ar);
			free(*ar);
			ft_lstadd_back(in, ft_lstnew((void *)&tmp, sizeof(int)));
			len++;
			ar++;
		}
		free(cp);
	}
	if (simple)
		simplify(*in);
	return (len);
}
