/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 13:38:34 by mbartole          #+#    #+#             */
/*   Updated: 2018/11/20 18:09:43 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ilen(long n)
{
	if (n < 0)
		return (1 + ilen(-n));
	if (n > 9)
		return (1 + ilen(n / 10));
	return (1);
}

char		*ft_itoa(int n)
{
	long	nb;
	char	*tmp;
	int		len;
	int		i;

	nb = n;
	len = ilen(nb);
	if (!(tmp = ft_strnew(len)))
		return (NULL);
	if (nb < 0)
	{
		tmp[0] = '-';
		nb = -nb;
	}
	i = len - 1;
	if (nb == 0)
		tmp[0] = '0';
	while (nb > 0)
	{
		tmp[i--] = nb % 10 + '0';
		nb = nb / 10;
	}
	return (tmp);
}
