/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 13:51:55 by mbartole          #+#    #+#             */
/*   Updated: 2019/04/12 16:15:31 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

# include "../libft.h"

typedef struct	s_list
{
	void			*cont;
	size_t			l_size;
	struct s_list	*next;
}				t_list;

/*
** malloc <list>, <list->cont>
** copy data from content to <list->cont>
*/

t_list			*ft_lstnew(void const *content, size_t content_size);

/* 
** just hook new element on the top of list (or push it to the back)
*/

void			ft_lstadd(t_list **alst, t_list *new);
void			ft_lstadd_back(t_list **alst, t_list *new);

void			ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));

void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));

int				ft_lstlen(t_list *lst);

t_list			*ft_lstcopy(t_list *lst);

#endif
