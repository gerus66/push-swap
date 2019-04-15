/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 19:04:59 by mbartole          #+#    #+#             */
/*   Updated: 2019/04/15 15:41:13 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H
# include "libft.h"
# include <stdarg.h>
# include <stdint.h>

typedef struct	s_print
{
	void		*arg;
	char		conv;
	char		flag[3];
	char		len_mod;
	int			width;
	int			prec;
}				t_print;

int				p_it(t_vector *out, t_vector *comm, t_print *p);
t_print			*c_it(char *comm, size_t c, va_list cur_a, va_list f_a);
void			parse_comm(char *comm, t_print *p, va_list cur_a, va_list f_a);
int				handle_num(char **comm, va_list tmp_a, va_list f_a);

/*
** ######################### CONVERSIONS #########################
*/

/*
** utils
*/

size_t			get_len_dec(size_t num, short base);
char			*abnormal(t_print *p);
char			*reg_st(char *st, t_print *pr);
char			*lch(wchar_t c);
char			*get_sig(double d, size_t prc);
short			round_sig(char **sig, size_t prc, char edge);
ssize_t			get_pow_exp(double d);

/*
** main functions
*/

char			*di_conv(ssize_t num, int pres, char sign);
char			*ff(t_print *p);

# define LEN(x) (x == 'h' || x == 'l' || x == 'L' || x == 'j' || x == 'z')
# define FLS(x) (x == 32 || x == 35 || x == 39 || x == 43 || x == 45 || x == 48)
# define SPR(x) (x == ',' || x == ';' || x == ':' || x == '_')
# define SPEC(x) (x == '*' || x == '.' || x == '$')
# define DG_0(x) (47 < x && x < 58)
# define DG(x) (48 < x && x < 58)
# define CONV_I(x) (x == 'd' || x == 'D' || x == 'i')
# define C_U1(x) (x == 'u' || x == 'U' || x == 'o' || x == 'O' || x == 'b')
# define C_U2(x) (x == 'x' || x == 'X' || x == 'p')
# define CONV_D(x) (x == 'f' || x == 'F' || x == 'E' || x == 'e')
# define C_S(x) (x == 'c' || x == 's')
# define C_WS(x) (x == 'C' || x == 'S')

# define INIT_V 100

#endif
