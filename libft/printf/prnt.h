/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prnt.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahugh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 22:00:41 by mbartole          #+#    #+#             */
/*   Updated: 2019/01/17 14:35:36 by ahugh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRNT_H
# define PRNT_H

# include "printf.h"

char	*di(t_print *p);
char	*ch(t_print *p);
char	*st(t_print *p);
char	*oux(t_print *p);
char	*ff(t_print *p);
char	*bb(t_print *p);
char	*ee(t_print *p);

# define PRNTS "dicsouxXpfFbeE"

char	*(*g_pr[14])(t_print *) = {di, di, ch, st, oux, oux, oux, oux, oux,
	ff, ff, bb, ee, ee};

#endif
