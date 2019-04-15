/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 15:39:22 by mbartole          #+#    #+#             */
/*   Updated: 2018/11/22 23:58:47 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	ch;
	unsigned char	*pc;
	size_t			i;

	ch = (unsigned char)c;
	pc = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (*pc == ch)
			return ((void *)pc);
		i++;
		pc++;
	}
	return (NULL);
}
