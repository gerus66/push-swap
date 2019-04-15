/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 07:10:21 by mbartole          #+#    #+#             */
/*   Updated: 2018/11/26 11:30:53 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	uc;

	uc = (unsigned char)c;
	i = 0;
	while (i < n && ((unsigned char *)src)[i] != uc)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		i++;
	}
	if (i < n && ((unsigned char *)src)[i] == uc)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		i++;
		return (&dst[i]);
	}
	return (NULL);
}
