/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 15:44:55 by mbartole          #+#    #+#             */
/*   Updated: 2018/11/23 13:17:02 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len;
	char	*j;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	if (!(j = ft_strnew(len)))
		return (NULL);
	i = -1;
	while (++i < len && *s1)
		j[i] = *s1++;
	i--;
	while (++i < len && *s2)
		j[i] = *s2++;
	return (j);
}
