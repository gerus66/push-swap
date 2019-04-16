/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 13:12:35 by mbartole          #+#    #+#             */
/*   Updated: 2019/04/17 00:18:00 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

static int	xclose(void *p)
{
	exit(clean(ERU_M, IBOX(p)->st));
}

static int	keyboard(int key, void *p)
{
	if (key == 53)
		exit(clean(ERU_M, IBOX(p)->st));
	if (key == 124)
		IBOX(p)->sleep /= 2;
	if (key == 123)
		if (IBOX(p)->sleep < I_MAX)
			IBOX(p)->sleep *= 2;
	if (key == 49)
		IBOX(p)->pause = IBOX(p)->pause ? 0 : 1;
	return (0);
}

static int	handle_stacks(void *p)
{
	char		*line;
	int			ret;
	static int	end = 0;
	t_imgbox	*ibox;

	if (end || (ibox = (t_imgbox *)(((int **)p)[2]))->pause)
		return (0);
	get_next_line(0, &line);
	if (ft_strcmp(line, "") || !(end = 1))
	{
		if (ibox->opt & 1)
			ft_printf(ibox->opt & 2 ? "{fma}%s{eoc}\n" : "%s\n", line);
		paint(*ibox, (void **)(((int **)(p))[0]), (void **)(((int **)(p))[1]),
				0);
		ret = do_one_comm(ibox->st, line, 1, 0);
		if (ibox->opt & 1)
			print_stacks(ibox->st->a, ibox->st->b,
					ibox->opt & 2 ? ret : 0, 22);
		paint(*ibox, (void **)(((int **)(p))[0]), (void **)(((int **)(p))[1]),
				ret);
	}
	if ((ret = check_stacks(ibox->st->a, ibox->count)) == 2 || end == 1)
		exit(clean(KO_M, ibox->st));
	end = ret == 1 ? 1 : end;
	return (0);
}

static void	create_elems(void **elems, t_imgbox ibox, char current)
{
	int		i;
	int		j;
	int		*data;
	int		val;

	i = -1;
	while (++i < ibox.count)
	{
		if (!(elems[i] = mlx_new_image(ibox.mlx,
						(i + 1) * ibox.w_step, ibox.h)))
			exit(clean(ERG_M, ibox.st));
		data = (int *)mlx_get_data_addr(elems[i], &val, &val, &val);
		j = -1;
		while (++j < (i + 1) * ibox.w_step * ibox.h)
			data[j] = current ? 0xE6AE2A : 0x50DBBB;
	}
}

void		init_graph(t_stacks *st, char opt, int count)
{
	t_imgbox	ibox;
	void		*elems[count];
	void		*curs[count];

	if (!(ibox.mlx = mlx_init()))
		exit(clean(ERG_M, st));
	if (!(ibox.wnd = mlx_new_window(ibox.mlx, WND_W, WND_H, "push-swap")))
		exit(clean(ERG_M, st));
	ibox.st = st;
	ibox.opt = opt;
	ibox.count = count;
	ibox.h = IMG_SIZE / ibox.count;
	ibox.w_step = IMG_SIZE / 2 / ibox.count;
	ibox.sleep = 100000;
	ibox.pause = 0;
	simplify(ibox.st->a, count);
	create_elems(elems, ibox, 0);
	create_elems(curs, ibox, 1);
	if (ibox.opt & 1)
		print_stacks(ibox.st->a, ibox.st->b, ibox.opt & 2 ? 12 : 0, 22);
	mlx_hook(ibox.wnd, 2, 0, keyboard, &ibox);
	mlx_hook(ibox.wnd, 17, 0, xclose, &ibox);
	mlx_loop_hook(ibox.mlx, handle_stacks,
			(int *[]){(int *)&elems, (int *)&curs, (int *)&ibox});
	mlx_loop(ibox.mlx);
}
