/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 23:43:20 by mbartole          #+#    #+#             */
/*   Updated: 2019/01/24 20:41:53 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoibase(const char *s, const char *base)
{
	int	res;
	int	sign;
	int	len;
	int	fl;
	int	i;

	len = ft_strlen(base);
	res = 0;
	while ((int)*s == 32 || ((int)*s >= 9 && (int)*s <= 13))
		s++;
	sign = (*s == '-' ? -1 : 1);
	if (sign == -1 || *s == '+')
		s++;
	fl = 1;
	while (*s && fl)
	{
		i = -1;
		fl = 0;
		while (++i < len)
			if (*(base + i) == *s && (fl = 1))
				res = res * len + i;
		s++;
	}
	return (res * sign);
}
