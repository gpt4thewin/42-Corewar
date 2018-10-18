/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_direct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbakhti <mbakhti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 02:49:48 by mbakhti           #+#    #+#             */
/*   Updated: 2019/03/08 19:14:22 by mbakhti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

_Bool	is_direct(char *tok, char next, t_pos cursor)
{
	if (!ft_isdigit(next) || next == SEPARATOR_CHAR
	|| ft_strchr(" \t\n\0", next))
	{
		if (ft_strlen(tok) > 1 && tok[0] == DIRECT_CHAR
		&& (ft_isdigit(tok[1]) || tok[1] == '-'))
			return (true);
	}
	return (false);
	(void)cursor;
}
