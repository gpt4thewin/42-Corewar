/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbakhti <mbakhti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 14:53:29 by mbakhti           #+#    #+#             */
/*   Updated: 2019/03/08 19:14:13 by mbakhti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef enum		e_token_type
{
	END,
	ENDLINE,
	WHITESPACE,
	SEPARATOR,
	COMMENT,
	COMMAND,
	STRING,
	LABEL,
	REGISTER,
	INDIRECT,
	INDIRECT_LABEL,
	DIRECT,
	DIRECT_LABEL,
	INSTRUCTION,
}					t_token_type;

typedef struct		s_pos
{
	int				lin;
	int				col;
}					t_pos;

typedef struct		s_token
{
	t_token_type	type;
	char			*value;
	t_pos			position;
	struct s_token	*next;
}					t_token;

typedef struct		s_func
{
	_Bool			(*ptrfunc)(char *tok, char next, t_pos cursor);
	t_token_type	token_type;
}					t_func;

void				lex_assembly(t_token **list, char *assembly);
_Bool				tokenized(char *tok, char next, t_token **last);
_Bool				is_whitespace(char *tok);
_Bool				is_endline(char *tok, char next, t_pos cursor);
_Bool				is_separator(char *tok, char next, t_pos cursor);
_Bool				is_comment(char *tok, char next, t_pos cursor);
_Bool				is_command(char *tok, char next, t_pos cursor);
_Bool				is_string(char *tok, char next, t_pos cursor);
_Bool				is_label(char *tok, char next, t_pos cursor);
_Bool				is_register(char *tok, char next, t_pos cursor);
_Bool				is_indirect(char *tok, char next, t_pos cursor);
_Bool				is_indirect_label(char *tok, char next, t_pos cursor);
_Bool				is_direct(char *tok, char next, t_pos cursor);
_Bool				is_direct_label(char *tok, char next, t_pos cursor);
_Bool				is_instruction(char *tok, char next, t_pos cursor);

#endif
