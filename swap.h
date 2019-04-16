/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 14:21:02 by mbartole          #+#    #+#             */
/*   Updated: 2019/04/17 00:18:02 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SWAP_H
# define SWAP_H

# include "libft.h"
# include "mlx.h"
# include <time.h>

# define I_MAX 2147483647
# define I_MIN -2147483648

# define ERR_M "Error\n"
# define ERM_M "Can malloc it, sorry:(\n"
# define OK_M "OK\n"
# define KO_M "KO\n"

# define ICONT(x) (*((int *)(x)->cont))
# define CCONT(x) ((char *)(x)->cont)

# define MAX(x, y) ((x) > (y) ? (x) : (y))
# define MIN(x, y) ((x) < (y) ? (x) : (y))
# define ABS(x) ((x) < 0 ? -(x) : (x))

# define WND_W 1200
# define WND_H 1100
# define IMG_SIZE 1000
# define ERG_M "Smth wrong with graphics, cant do it:(\n"
# define ERU_M "User close the window\n"
# define IBOX(x) ((t_imgbox *)x)

typedef struct	s_stacks
{
	t_list	*a;
	t_list	*b;
	t_list	*comm;
	t_list	*local_comm;
	int		len_a;
	int		len_b;
}				t_stacks;

typedef struct	s_imgbox
{
	void		*mlx;
	void		*wnd;
	t_stacks	*st;
	int			count;
	char		opt;
	int			*data;
	int			h;
	int			w_step;
	long		sleep;
	char		pause;
}				t_imgbox;

/*
** operations with stack /operations.c (4)/
*/

void			swap_stack(t_list **st);
void			push_stack(t_list **src, t_list **dst);
void			rotate_stack(t_list **st);
void			r_rotate_stack(t_list **st);

/*
** operations with commands /utils_comm.c (4)/
*/

int				do_one_comm(t_stacks *all, char *line, char free_line, char fl);
void			do_all_comm(t_stacks *all, t_list *comm);
void			add_comm(t_stacks *all, t_list **comm, char *name);
void			add_and_do(t_stacks *all, t_list **comm, char *name);

/*
** some improvement of commands list /improve_comm.c (5)/
*/

void			improve_comm_swap(t_list **comm);
void			improve_comm_dub(t_list **comm);

/*
** read stack A from argv, check validity
** initialize [in], return length of [in]
** if [simplify] replace numbers by its order /init_all.c (5)/
*/

void			init_all(t_stacks *all, char **argv, int count, char simplify);
void			simplify(t_list *in, int count);

/*
** get sequence of diffs for current stack, or just sort it
** can be straight or reverse
*/

void			get_diff(t_list *in, int *ret, char razn, char reverse);

/*
** choose sorted sequence
*/

void			choose_sequence(int *razn, int count, t_stacks *all);

/*
** push back to A (in cycle) /back_to_a.c (4)/
*/

void			back_to_a(t_stacks *all);
int				get_rot(t_list *st, int *param, char *fl);
void			perform_rot(t_stacks *all, int to_push, char fl);

/*
** final: push back to A reversed sorted B, rotate A to start /last_push.c (3)/
*/

void			last_push(t_stacks *all);

/*
** sort remains in B (try it several times) /last.c (4)/
*/

t_list			*last(t_stacks *origin, int count);

/*
** utils /utils.c (5)/
*/

int				clean(char *msg, t_stacks *all);
int				last_elem(t_list *stack);
int				cut_tail(t_list **comm, char *name);
char			can_insert(int val, int first, int last);
char			can_insert_rev(int val, t_list *st);

/*
** checker utils - for checker and for graphic /utils_checker.c (2)/
*/

int				check_stacks(t_list *st, int count);
void			print_stacks(t_list *a, t_list *b, int comm, int first);
void			paint(t_imgbox ibox, void **elems, void **curs, int code);

/*
** graphic visualisation
*/

void			init_graph(t_stacks *all, char opt, int count);

#endif
