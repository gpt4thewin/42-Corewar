/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbakhti <mbakhti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 02:49:48 by mbakhti           #+#    #+#             */
/*   Updated: 2019/03/08 19:14:16 by mbakhti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

_Bool	is_string(char *tok, char next, t_pos cursor)
{
	int		last_char;

	if (ft_strchr(" \t\n\0", next))
	{
		last_char = ft_strlen(tok) - 1;
		if (last_char > 0 && tok[0] == '"' && tok[last_char] == '"')
			return (true);
	}
	return (false);
	(void)cursor;
}
