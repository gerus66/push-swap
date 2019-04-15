/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 20:18:24 by mbartole          #+#    #+#             */
/*   Updated: 2018/11/22 05:21:18 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int		i;
	int		j;
	int		i_res;

	if (needle[0] == '\0')
		return ((char *)haystack);
	i = -1;
	while (haystack[++i])
	{
		j = 0;
		if (haystack[i] == needle[j])
		{
			i_res = i;
			while (haystack[i++] == needle[j++] && haystack[i - 1])
				;
			if (needle[j - 1] == '\0' || needle[j - 2] == '\0')
				return ((char *)&haystack[i_res]);
			else
				return (ft_strstr(&haystack[i_res + 1], needle));
		}
	}
	return (0);
}
