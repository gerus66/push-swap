/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 13:12:35 by mbartole          #+#    #+#             */
/*   Updated: 2019/04/17 14:37:29 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "swap.h"

static int	xclose(void *p)
{
	int	ret;

	ret = check_stacks(IBOX(p)->st->a, IBOX(p)->count);
	if (ret == 1)
		exit(clean(OK_M, IBOX(p)->st));
	if (ret == 2)
		exit(clean(KO_M, IBOX(p)->st));
	else
		exit(clean(ERR_M, IBOX(p)->st));
}

static int	keyboard(int key, void *p)
{
	int	ret;

	if (key == 53)
	{
		ret = check_stacks(IBOX(p)->st->a, IBOX(p)->count);
		if (ret == 1)
			exit(clean(OK_M, IBOX(p)->st));
		if (ret == 2)
			exit(clean(KO_M, IBOX(p)->st));
		else
			exit(clean(ERR_M, IBOX(p)->st));
	}
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
	static char	*line = NULL;
	int			r;
	static int	counter = 1;
	t_imgbox	*ib;

	if (!counter || (ib = (t_imgbox *)(((int **)p)[2]))->pause)
		return (0);
	if (counter % 2 && get_next_line(0, &line) &&
			(ft_strcmp(line, "") || (counter = 0)))
	{
		if (counter++ && ib->opt & 1)
			ft_printf(ib->opt & 2 ? "{fma}%s{eoc}\n" : "%s\n", line);
		paint(*ib, (void **)(((int **)(p))[0]), (void **)(((int **)(p))[1]),
				code_comm(line, 1, 0));
	}
	else if (counter && (r = code_comm(line, 0, 0)))
	{
		do_one_comm(ib->st, line, 1, 0);
		if (counter-- && ib->opt & 1)
			print_stacks(ib->st->a, ib->st->b, ib->opt & 2 ? r : 0, 22);
		paint(*ib, (void **)(((int **)(p))[0]), (void **)(((int **)(p))[1]), r);
	}
	if ((r = check_stacks(ib->st->a, ib->count)) == 2 || counter == 0)
		exit(clean(KO_M, ib->st));
	return ((counter = r == 1 ? 0 : counter));
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
