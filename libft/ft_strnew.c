/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 16:29:19 by mbartole          #+#    #+#             */
/*   Updated: 2018/11/27 12:44:16 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*new;
	size_t	i;

	if (size + 1 == 0)
		return (NULL);
	new = (char *)malloc(sizeof(char) * size + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (i <= size)
		new[i++] = '\0';
	return (new);
}
