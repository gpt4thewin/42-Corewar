/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_instruction.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juazouz <juazouz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 16:22:21 by mbakhti           #+#    #+#             */
/*   Updated: 2019/04/03 12:38:48 by juazouz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static _Bool	is_param(t_token token)
{
	if (token.type == REGISTER || token.type == INDIRECT
		|| token.type == INDIRECT_LABEL || token.type == DIRECT
		|| token.type == DIRECT_LABEL)
		return (true);
	return (false);
}

static void		push_param(t_token **token, t_instr **last)
{
	int		i;

	if (!is_param(**token))
		syntax_error(**token);
	i = 0;
	while (is_param(**token))
	{
		copy_token(**token, &(*last)->param[i]);
		*token = (*token)->next;
		if ((*token)->type == SEPARATOR)
		{
			i++;
			*token = (*token)->next;
			if (i >= MAX_ARGS_NUMBER || !is_param(**token))
				syntax_error(**token);
		}
		else if ((*token)->type != ENDLINE && (*token)->type != COMMENT
		&& (*token)->type != END)
			syntax_error(**token);
	}
}

static void		push_op(t_token **token, t_instr **last)
{
	if ((*token)->type == INSTRUCTION)
	{
		copy_token(**token, &(*last)->op);
		*token = (*token)->next;
		if ((*token)->type == END)
			syntax_error(**token);
	}
	else if ((*token)->type != END)
		syntax_error(**token);
}

void			push_instruction(t_token **token, t_instr **last)
{
	push_op(token, last);
	if ((*token)->type != END)
		push_param(token, last);
}
