/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_direct_label.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbakhti <mbakhti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 02:49:48 by mbakhti           #+#    #+#             */
/*   Updated: 2019/03/08 19:14:22 by mbakhti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static _Bool	check_lexical_error(char *tok, t_pos cursor)
{
	size_t	i;

	i = 2;
	while (i < ft_strlen(tok))
	{
		if (!ft_strchr(LABEL_CHARS, tok[i]))
		{
			ft_printf("Lexical error at [%d:%d]\n", cursor.lin, cursor.col + i);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (true);
}

_Bool			is_direct_label(char *tok, char next, t_pos cursor)
{
	if (next == SEPARATOR_CHAR || ft_strchr(" \t\n\0", next))
	{
		if (ft_strlen(tok) > 2 && tok[0] == DIRECT_CHAR && tok[1] == LABEL_CHAR)
			return (check_lexical_error(tok, cursor));
	}
	return (false);
}
