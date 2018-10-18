/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_register.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbakhti <mbakhti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 02:49:48 by mbakhti           #+#    #+#             */
/*   Updated: 2019/03/08 19:14:17 by mbakhti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

_Bool	is_register(char *tok, char next, t_pos cursor)
{
	size_t	i;

	if (!ft_isdigit(next) || next == SEPARATOR_CHAR
	|| ft_strchr(" \t\n\0", next))
	{
		if (ft_strlen(tok) > 1 && tok[0] == 'r' && ft_strlen(tok) < 4)
		{
			i = 1;
			while (i < ft_strlen(tok))
			{
				if (!ft_isdigit(tok[i]))
					return (false);
				i++;
			}
			return (true);
		}
	}
	return (false);
	(void)cursor;
}
