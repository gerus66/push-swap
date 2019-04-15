/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   di_conv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 16:42:21 by ahugh             #+#    #+#             */
/*   Updated: 2019/01/16 14:31:47 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

/*
** sign takes value 32 (space), 43 (plus) && any other value (default behavior)
** pres set the number precision
*/

char	*di_conv(ssize_t num, int pres, char sign)
{
	char		*result;
	size_t		u_num;
	int			len;

	len = 1;
	u_num = num;
	if ((sign == 32 || sign == 43 || sign == 45 || num < 0) && ++len)
		num == 0 && pres == 0 ? pres : ++pres;
	num < 0 ? (u_num *= -1) : u_num;
	while (++len && u_num > 9)
		u_num /= 10;
	len = (pres >= len ? (pres + 1) : len);
	if (!(result = (char*)malloc((num == 0 && pres == 0 ? 2 : len))))
		return (0);
	result[(num == 0 && pres == 0 ? 1 : --len)] = 0;
	u_num = num;
	num < 0 ? (u_num *= -1) : 1;
	if (!(num == 0 && pres == 0))
		while (len-- && (result[len] = (u_num % 10) + 48) != 127)
			u_num /= 10;
	if (sign == 32 || sign == 43 || sign == 45)
		result[0] = sign;
	num < 0 ? (result[0] = 45) : 1;
	return (result);
}

char	*di(t_print *p)
{
	int	pres;

	pres = (p->prec == -1 ? 1 : p->prec);
	if (p->len_mod == 'g')
		return (di_conv((char)p->arg, pres, p->flag[2]));
	else if (p->len_mod == 'h')
		return (di_conv((short)p->arg, pres, p->flag[2]));
	else if (p->len_mod == 'l')
		return (di_conv((long)p->arg, pres, p->flag[2]));
	else if (p->len_mod == 'm')
		return (di_conv((long long)p->arg, pres, p->flag[2]));
	else
		return (di_conv((int)p->arg, pres, p->flag[2]));
}
