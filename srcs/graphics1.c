/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 12:02:43 by mbartole          #+#    #+#             */
/*   Updated: 2019/04/22 12:03:25 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

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
