/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 14:41:55 by mbartole          #+#    #+#             */
/*   Updated: 2019/01/26 13:55:49 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

void	ft_lstdelone(t_list **alst, void (*del)(void *, size_t))
{
	if (!alst || !(*alst))
		return ;
	if (del)
		del((*alst)->content, (*alst)->content_size);
	else
		free((*alst)->content);
	free(*alst);
	*alst = NULL;
}
