/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 15:39:22 by mbartole          #+#    #+#             */
/*   Updated: 2018/11/22 08:51:25 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	ch;
	char	*tmp;

	tmp = NULL;
	ch = (char)c;
	while (*s)
	{
		if (*s == ch)
			tmp = (char *)s;
		s++;
	}
	if (ch == 0)
		return ((char *)s);
	return (tmp);
}
