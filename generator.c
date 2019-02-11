/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 15:04:16 by mbartole          #+#    #+#             */
/*   Updated: 2019/02/11 23:20:36 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char **argv)
{
	int	tmp;
	int	j;

	if (argc != 2)
		return (0);
	int count = atoi(argv[1]);
	int *ar = (int *)malloc(sizeof(int) * count);
	srand(time(NULL));
	int	i = 0;
	while (i < count)
	{
		tmp = rand() % 1000;
		j = -1;
		while (++j < i)
			if (tmp == ar[j])
				break ;
		if (j == i)
		{
			ar[i] = tmp;
			printf("%d ", tmp);
			i++;
		}
	}
	return (0);
}
