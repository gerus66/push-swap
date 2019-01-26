/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 23:43:20 by mbartole          #+#    #+#             */
/*   Updated: 2018/11/26 11:00:56 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int		len;
	char	*cp;
	char	*new;

	if (!s)
		return (NULL);
	cp = (char *)s + ft_strlen(s) - 1;
	while (*s && (*s == ' ' || *s == '\n' || *s == '\t'))
		s++;
	len = ft_strlen(s);
	while (*cp && (*cp == ' ' || *cp == '\n' || *cp == '\t'))
	{
		len--;
		cp--;
	}
	if (len <= 0)
		return (ft_strdup(s));
	if (!(new = ft_strnew(len)))
		return (NULL);
	while (s != cp)
		*new++ = *s++;
	*new = *s;
	return (new - len + 1);
}
