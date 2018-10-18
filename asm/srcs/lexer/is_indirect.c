/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_indirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbakhti <mbakhti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 02:49:48 by mbakhti           #+#    #+#             */
/*   Updated: 2019/03/08 19:14:21 by mbakhti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static _Bool	is_num(char *tok)
{
	int		i;

	i = 0;
	if (tok[i] == '-' && !tok[++i])
		return (false);
	while (tok[i])
	{
		if (!ft_isdigit(tok[i]))
			return (false);
		i++;
	}
	return (true);
}

_Bool			is_indirect(char *tok, char next, t_pos cursor)
{
	if (next == SEPARATOR_CHAR || ft_strchr(" \t\n\0", next))
	{
		if ((tok[0] == '-' && !ft_isdigit(next)) || ft_isdigit(tok[0]))
			return (is_num(tok));
	}
	return (false);
	(void)cursor;
}
