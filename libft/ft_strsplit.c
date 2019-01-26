/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 20:34:22 by mbartole          #+#    #+#             */
/*   Updated: 2018/11/27 11:21:18 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *str, char c)
{
	int		count;
	int		fl;

	if (!str)
		return (0);
	count = 0;
	while (*str)
	{
		while (*str == c)
			str++;
		fl = 0;
		while (*str && *str++ != c)
			fl = 1;
		if (fl)
			count++;
	}
	return (count);
}

static int	count_letters(char const **str, char c)
{
	int		count;

	count = 0;
	while (**str)
	{
		while (**str == c)
			(*str)++;
		while (**str && **str != c)
		{
			(*str)++;
			count++;
		}
		break ;
	}
	*str = *str - count;
	return (count);
}

static void	free_previous(char **ar, int num)
{
	int	i;

	i = -1;
	while (++i < num)
		free(ar[i]);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**ar;
	int		count;
	int		countl;
	int		i;
	int		j;

	count = count_words(s, c);
	if (!s || !(ar = (char**)malloc(sizeof(char*) * count + 1)))
		return (NULL);
	i = -1;
	while (++i < count)
	{
		countl = count_letters(&s, c);
		if (!(ar[i] = ft_strnew(countl)))
		{
			free_previous(ar, i);
			free(ar);
			return (NULL);
		}
		j = -1;
		while (++j < countl)
			ar[i][j] = s++[0];
	}
	ar[count] = 0;
	return (ar);
}
