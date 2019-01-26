/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 22:38:10 by mbartole          #+#    #+#             */
/*   Updated: 2019/01/25 19:14:33 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vector	*find_v(t_avltree **tr, int fd)
{
	t_vector	*v;

	v = ft_tree_search(*tr, fd);
	if (!v)
	{
		ft_vnew(&v, BUFF_SIZE + 1);
		ft_tree_insert(tr, fd, v, sizeof(t_vector));
		free(v);
		v = ft_tree_search(*tr, fd);
	}
	return (v);
}

int			v_clean(int ret, char **line, t_avltree **tr, int fd)
{
	free(((t_vector *)ft_tree_search(*tr, fd))->cont);
	*tr = ft_tree_delnode(*tr, fd);
	*line = NULL;
	return (ret);
}

int			v_extract(t_vector *v, char **new, int theend)
{
	char	*newst;
	size_t	curlen;

	if (!theend && (newst = ft_strchr(((char *)v->cont + v->offset), 10)))
	{
		curlen = (size_t)(newst - ((char *)v->cont + v->offset));
		if (!(*new = ft_strsub((char *)v->cont, v->offset, curlen)))
			return (0);
		v->offset += curlen + 1;
		if (v->v_size > BUFF_SIZE + 1)
			v = ft_vresize(v);
	}
	else if (theend)
	{
		if (!(*new = ft_strsub(v->cont, v->offset, v->len - v->offset)))
			return (0);
		v->offset += (v->len - v->offset);
	}
	else
		*new = NULL;
	return (1);
}

int			get_next_line(const int fd, char **l)
{
	char				buf[BUFF_SIZE + 1];
	static t_avltree	*tr = NULL;
	t_vector			*v;
	int					r;

	if (BUFF_SIZE <= 0 || !l || !(v = find_v(&tr, fd)))
		return (-1);
	if (v->len - v->offset && v_extract(v, l, 0) && *l)
		return (1);
	while ((r = read(fd, buf, BUFF_SIZE)))
	{
		if (r == -1)
			return (v_clean(r, l, &tr, fd));
		buf[r] = '\0';
		if (!ft_vadd(v, buf, r))
			return (v_clean(-1, l, &tr, fd));
		if (v->len - v->offset && v_extract(v, l, 0) && *l)
			return (1);
	}
	if (v->len - v->offset && v_extract(v, l, 0) && *l)
		return (1);
	if (v->len - v->offset && v_extract(v, l, 1) && *l)
		return (1);
	return (v_clean(r, l, &tr, fd));
}
