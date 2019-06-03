/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 19:28:54 by mbartole          #+#    #+#             */
/*   Updated: 2019/04/15 15:57:46 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include "libft.h"

typedef struct	s_vector
{
	void	*cont;
	size_t	v_size;
	size_t	len;
	ssize_t	offset;
}				t_vector;

/*
** malloc pointer *v for new vector and return it
** malloc <cont> of vector for size <v_size>
** set <v_size> to v_size, set <len> and <offset> to 0
** if smth wrong, return NULL
*/

t_vector		*ft_vnew(t_vector **v, size_t v_size);
t_vector		*ft_vadd(t_vector *v, void *cont, size_t c_size);
t_vector		*ft_vresize(t_vector *v);
void			*ft_vreset(t_vector *v);
void			ft_vprint(t_vector v);
void			ft_vdel(t_vector **v);

#endif
