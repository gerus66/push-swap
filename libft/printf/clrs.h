/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clrs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbartole <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 20:36:52 by mbartole          #+#    #+#             */
/*   Updated: 2019/01/16 21:52:57 by mbartole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLRS_H
# define CLRS_H

char g_clrs[8][2] = {"gr", "re", "gn", "ye", "bl", "ma", "cy", "wh"};

# define GR(x) (x[2] == 'g' && x[3] == 'r')
# define R(x) (x[2] == 'r' && x[3] == 'e')
# define GN(x) (x[2] == 'g' && x[3] == 'n')
# define Y(x) (x[2] == 'y' && x[3] == 'e')
# define B(x) (x[2] == 'b' && x[3] == 'l')
# define M(x) (x[2] == 'm' && x[3] == 'a')
# define C(x) (x[2] == 'c' && x[3] == 'y')
# define W(x) (x[2] == 'w' && x[3] == 'h')
# define EOC(x) (x[1] == 'e' && x[2] == 'o' && x[3] == 'c')

#endif
