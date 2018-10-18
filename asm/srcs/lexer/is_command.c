/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbakhti <mbakhti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 02:49:48 by mbakhti           #+#    #+#             */
/*   Updated: 2019/03/08 19:14:22 by mbakhti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

_Bool	is_command(char *tok, char next, t_pos cursor)
{
	if (ft_strchr(" \"\t\n\0", next))
	{
		if (ft_strequ(NAME_CMD_STRING, tok)
		|| ft_strequ(COMMENT_CMD_STRING, tok))
			return (true);
	}
	return (false);
	(void)cursor;
}
