/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juazouz <juazouz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 02:49:48 by mbakhti           #+#    #+#             */
/*   Updated: 2019/04/10 15:16:04 by juazouz          ###   ########.fr       */
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
