/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoulas <agoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 15:14:28 by mbakhti           #+#    #+#             */
/*   Updated: 2019/03/28 18:44:29 by agoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	end_lex(t_token *last, t_pos cursor, char *tok, char *assembly)
{
	last->position = cursor;
	ft_strdel(&tok);
	ft_strdel(&assembly);
}

static void	move_cursor(t_pos *cursor, char c)
{
	if (c == '\n')
	{
		cursor->lin++;
		cursor->col = 1;
	}
	else
		cursor->col++;
}

static void	reset_tok(char **tok, int size, int *index)
{
	ft_bzero(*tok, size);
	*index = -1;
}

static void	init_lexer(t_token **list, char **tok, int size, t_pos *cursor)
{
	*list = ft_memalloc(sizeof(t_token));
	*tok = ft_strnew(size);
	cursor->lin = 1;
	cursor->col = 1;
	(*list)->type = END;
	(*list)->value = NULL;
	(*list)->position = *cursor;
	(*list)->next = NULL;
}

void		lex_assembly(t_token **list, char *assembly)
{
	t_pos	cursor;
	t_token	*last;
	char	*tok;
	int		i;
	int		j;

	init_lexer(list, &tok, ft_strlen(assembly), &cursor);
	last = *list;
	i = 0;
	j = 0;
	while (assembly[i])
	{
		tok[j] = assembly[i];
		if (is_whitespace(tok) || tokenized(tok, assembly[i + 1], &last))
		{
			reset_tok(&tok, ft_strlen(assembly), &j);
			move_cursor(&cursor, assembly[i]);
			last->position = cursor;
		}
		else
			move_cursor(&cursor, assembly[i]);
		i++;
		j++;
	}
	end_lex(last, cursor, tok, assembly);
}
