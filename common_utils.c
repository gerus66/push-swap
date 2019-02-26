/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 20:35:30 by mbartole          #+#    #+#             */
/*   Updated: 2019/02/26 04:39:44 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

static int clean(char *msg)
{
	ft_putstr(msg);
	return (0);
}

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

//TODO function to check unique of each element

int				argv_to_list(t_list **in, char **argv, int count)
{
	int		i;
	char	**ar;
	int		tmp;

	i = 0;
	while (++i <= count)
	{
		ar = ft_strsplit(argv[i], ' ');
		while (*ar)
		{
			tmp = atoi_check(*ar);
			ft_lstadd_back(in, ft_lstnew((void *)&tmp, sizeof(int)));
			ar++;
		}
	}
	return (ft_lstlen(*in));
}

void	do_one_comm(t_list **a, t_list **b, t_list *comm)
{
	char	*line;
	int		fl;

	fl = 0;
	line = (char *)comm->cont;
	if ((!ft_strcmp(line, "sa") || !ft_strcmp(line, "ss")) && (fl = 1))
		swap_stack(a);
	if ((!ft_strcmp(line, "sb") || !ft_strcmp(line, "ss")) && (fl = 1))
		swap_stack(b);
	if ((!ft_strcmp(line, "ra") || !ft_strcmp(line, "rr")) && (fl = 1))
		rotate_stack(a);
	if ((!ft_strcmp(line, "rb") || !ft_strcmp(line, "rr")) && (fl = 1))
		rotate_stack(b);
	if ((!ft_strcmp(line, "rra") || !ft_strcmp(line, "rrr")) && (fl = 1))
		r_rotate_stack(a);
	if ((!ft_strcmp(line, "rrb") || !ft_strcmp(line, "rrr")) && (fl = 1))
		r_rotate_stack(b);
	if (!ft_strcmp(line, "pa") && (fl = 1))
		push_stack(b, a);
	else if (!ft_strcmp(line, "pb") && (fl = 1))
		push_stack(a, b);
	if (!fl)
		exit(clean(ERR_M));//TODO
}

void	do_all_comm(t_list **a, t_list **b, t_list *comm)
{
	while (comm)
	{
		do_one_comm(a, b, comm);
		comm = comm->next;
	}
}
