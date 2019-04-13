/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 14:21:02 by mbartole          #+#    #+#             */
/*   Updated: 2019/04/13 17:10:41 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

# include "libft/libft.h"

# include <stdio.h> //TODO

#define I_MAX 2147483647
#define I_MIN -2147483648

# define ERR_M "Error\n"
# define ERM_M "Can malloc it, sorry:(\n"
# define OK_M "OK\n"
# define KO_M "KO\n"

# define ICONT(x) (*((int *)(x)->cont))
# define CCONT(x) ((char *)(x)->cont)

# define MAX(x, y) ((x) > (y) ? (x) : (y))
# define MIN(x, y) ((x) < (y) ? (x) : (y))
# define ABS(x) ((x) < 0 ? -(x) : (x))

typedef struct	s_stacks
{
	t_list	*a;
	t_list	*b;
	t_list	*comm;
	t_list	*local_comm;
	int		len_a;
	int		len_b;
}				t_stacks;

/*
** operations with stack /operations.c/
*/

void	swap_stack(t_list **st);
void	push_stack(t_list **src, t_list **dst);
void	rotate_stack(t_list **st);
void	r_rotate_stack(t_list **st);

/*
** operations with commands /utils_comm.c/
*/

void	do_one_comm(t_stacks *all, char *line, char free_line);
void	do_all_comm(t_stacks *all, t_list *comm);
void	add_comm(t_stacks *all, t_list **comm, char *name);
void	add_and_do(t_stacks *all, t_list **comm, char *name);

/*
** read stack A from argv, check validity
** initialize [in], return length of [in]
** if [simplify] replace numbers by its order
*/

void		init_all(t_stacks *all, char **argv, int count, char simplify);

/*
** get sequence of diffs for current stack, or just sort it
** can be straight or reverse 
*/

void		get_diff(t_list *in, int *ret, char razn, char reverse);

/*
** choose sorted sequence
*/

void	choose_sequence(int *razn, int count);

/*
** push to B (one time, the first)
*/

void	push_b(int *standing, t_stacks *all);
void    improve_comm_dub(t_list **comm);

/*
** push back to A (in cycle)
*/

void		back_to_a(t_stacks *all);
int			get_rot(t_list *st, int * param, char *fl);
void		perform_rot(t_stacks *all, int to_push, char fl);

/*
** push back to A reversed sorted B
*/

void	  	last_push(t_stacks *all);

/*
** sort remains in B
*/

t_list		*last(t_stacks *origin, int count);

/*
** utils
*/

int		clean(char *msg, t_stacks *all);


t_list  *get_to_push(int *seq, t_list *st);
void    print_seq(int *seq, int count);
void    print_comm(t_list *comm);
void	print_stacks(t_list *a, t_list *b);
void	print_stack(t_list *a);
int     last_elem(t_list *stack);
int     prelast_elem(t_list *stack);
int	    cut_tail(t_list **comm, char *name);
char	can_insert(int val, int first, int last);
char	can_insert_rev(int val, t_list *st);
t_list	*atoi_stack(t_list *stack);

#endif
