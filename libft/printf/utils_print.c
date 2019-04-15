/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 01:33:44 by mbartole          #+#    #+#             */
/*   Updated: 2019/01/16 02:02:21 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

/*
** handle $ (copy [f_a] in [tmp_a], then move it on [num] steps) if there is
** one and return 0
** or return number, extracted from command string
*/

int		handle_num(char **comm, va_list tmp_a, va_list f_a)
{
	int		num;

	num = 0;
	while (DG_0(**comm))
	{
		num = num * 10 + **comm - 48;
		(*comm)++;
	}
	if (!num)
		return (0);
	if (**comm == '$')
	{
		va_copy(tmp_a, f_a);
		while (num-- > 1)
			va_arg(tmp_a, void*);
		(*comm)++;
		return (0);
	}
	return (num);
}
