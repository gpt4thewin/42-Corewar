/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_label.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juazouz <juazouz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 02:49:48 by mbakhti           #+#    #+#             */
/*   Updated: 2019/04/01 13:59:28 by juazouz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static _Bool	check_lexical_error(char *tok, t_pos cursor)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(tok) - 1)
	{
		if (!ft_strchr(LABEL_CHARS, tok[i]))
		{
			ft_fprintf(2, "Lexical error at [%d:%d]\n", cursor.lin,
				cursor.col + i);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (true);
}

_Bool			is_label(char *tok, char next, t_pos cursor)
{
	if (tok[0] != COMMENT_CHAR && tok[0] != ';' && tok[0] != '\"'
	&& (next == SEPARATOR_CHAR || ft_strchr(" \t\n\0", next)
	|| !ft_strchr(LABEL_CHARS, next)))
	{
		if (ft_strlen(tok) > 1 && tok[ft_strlen(tok) - 1] == LABEL_CHAR)
			return (check_lexical_error(tok, cursor));
	}
	return (false);
}
