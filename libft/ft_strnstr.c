/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 20:18:24 by mbartole          #+#    #+#             */
/*   Updated: 2018/11/23 08:55:40 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hayst, const char *needl, size_t len)
{
	int			j;
	size_t		i;
	int			i_res;

	if (needl[0] == '\0')
		return ((char *)hayst);
	i = 0;
	while (hayst[i] && i < len)
	{
		j = 0;
		if (hayst[i] == needl[j])
		{
			i_res = i;
			while (hayst[i++] == needl[j++] && hayst[i - 1] && i <= len)
				;
			if (needl[j - 1] == '\0' || needl[j - 2] == '\0')
				return ((char *)&hayst[i_res]);
			else
				return (ft_strnstr(&hayst[i_res + 1], needl, len - i_res - 1));
		}
		i++;
	}
	return (0);
}
