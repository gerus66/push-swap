/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 14:24:19 by mbartole          #+#    #+#             */
/*   Updated: 2019/04/17 13:37:06 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

static int	color_a(int *comm, int *first, t_list *st)
{
	int	ret;

	ret = 0;
	if ((*comm && *comm % 10 != 2 && ((*first / 10 && *comm / 10 != 3) ||
			(!st->next && *comm / 10 == 3))))
		ret = 1;
	*first = (*first / 10 == 2 && *comm / 10 == 1) ? *first - 10 : *first % 10;
	return (ret);
}

static int	color_b(int *comm, int *first, t_list *st)
{
	int	ret;

	ret = 0;
	if ((*comm && *comm % 10 != 1 && ((*first % 10 && *comm / 10 != 3) ||
			(!st->next && *comm / 10 == 3))))
		ret = 1;
	*first -= (*first % 10 == 2 && *comm / 10 == 1) ? 1 : *first % 10;
	return (ret);
}

void		print_stacks(t_list *a, t_list *b, int comm, int first)
{
	int		div;

	div = ft_lstlen(a) - ft_lstlen(b);
	while (a || b)
	{
		if (div >= 0 && ft_printf(color_a(&comm, &first, a) ?
					"{bgn}{fgr}%6d{eoc} " : "%6d ", ICONT(a)))
			a = a->next;
		else
			ft_printf("%6c ", ' ');
		if (div <= 0 && ft_printf(color_b(&comm, &first, b) ?
					"{bgn}{fgr}%6d{eoc}\n" : "%6d\n", ICONT(b)))
			b = b->next;
		else
			ft_printf("%6c\n", ' ');
		if (div > 0)
			div--;
		if (div < 0)
			div++;
	}
	ft_printf("{fbl}%6c %6c\n%6c %6c\n\n{eoc}", '_', '_', 'a', 'b');
}

int			check_stacks(t_list *st, int count)
{
	int	prev;

	if (!st)
		return (0);
	if (!st->next && count == 1)
		return (1);
	prev = *((int *)st->cont);
	st = st->next;
	count--;
	while (st && count--)
	{
		if (*((int *)st->cont) < prev)
			return (0);
		else if (*((int *)st->cont) == prev)
			return (2);
		prev = *((int *)st->cont);
		st = st->next;
	}
	if (count == 0)
		return (1);
	return (0);
}

void		paint(t_imgbox ibox, void **elems, void **curs, int comm)
{
	int		y;
	t_list	*cp;
	int		first;

	first = 22;
	usleep(ibox.sleep);
	mlx_clear_window(ibox.mlx, ibox.wnd);
	cp = ibox.st->a;
	y = WND_H - IMG_SIZE + (ibox.count - ft_lstlen(ibox.st->a) - 1) * ibox.h;
	while (cp && (y += ibox.h))
	{
		mlx_put_image_to_window(ibox.mlx, ibox.wnd, color_a(&comm, &first, cp)
			? curs[ICONT(cp)] : elems[ICONT(cp)], (WND_W - IMG_SIZE) / 4 +
			(ibox.count - ICONT(cp)) * ibox.w_step / 2, y);
		cp = cp->next;
	}
	cp = ibox.st->b;
	y = WND_H - IMG_SIZE + (ibox.count - ft_lstlen(ibox.st->b) - 1) * ibox.h;
	while (cp && (y += ibox.h))
	{
		mlx_put_image_to_window(ibox.mlx, ibox.wnd, color_b(&comm, &first, cp)
			? curs[ICONT(cp)] : elems[ICONT(cp)], WND_W / 2 + (WND_W -
			IMG_SIZE) / 4 + (ibox.count - ICONT(cp)) * ibox.w_step / 2, y);
		cp = cp->next;
	}
}
