/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoulas <agoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 16:38:07 by mbakhti           #+#    #+#             */
/*   Updated: 2019/03/28 18:44:15 by agoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	init_instruction(t_instr **instruction, int op_number)
{
	int		i;

	(*instruction)->op_number = op_number;
	(*instruction)->size = 0;
	(*instruction)->op = (t_token){0, NULL, {0, 0}, NULL};
	i = 0;
	while (i < MAX_ARGS_NUMBER)
	{
		(*instruction)->param[i] = (t_token){0, NULL, {0, 0}, NULL};
		(*instruction)->arg[i] = 0;
		i++;
	}
	(*instruction)->opcode = 0;
	(*instruction)->argcode = 0;
	(*instruction)->next = NULL;
}

static void	init_label(t_lab **label, int op_number)
{
	(*label)->op_number = op_number;
	(*label)->label = (t_token){0, NULL, {0, 0}, NULL};
	(*label)->offset = 0;
	(*label)->next = NULL;
}

static void	init_env(t_lab **labels, t_lab **last_lab, t_instr **instructions,
t_instr **last_op)
{
	*labels = ft_memalloc(sizeof(t_lab));
	*last_lab = *labels;
	init_label(last_lab, 0);
	*instructions = ft_memalloc(sizeof(t_instr));
	*last_op = *instructions;
	init_instruction(last_op, 0);
}

static void	push_labels(t_token **token, t_lab **last, int op_number)
{
	while ((*token)->type == ENDLINE || (*token)->type == COMMENT
	|| (*token)->type == LABEL)
	{
		if ((*token)->type == LABEL)
		{
			copy_token(**token, &(*last)->label);
			(*last)->label.value[ft_strlen((*last)->label.value) - 1] = '\0';
			(*last)->next = ft_memalloc(sizeof(t_lab));
			*last = (*last)->next;
			init_label(last, op_number);
		}
		*token = (*token)->next;
	}
}

void		check_syntax(t_token *token, t_lab **labels, t_instr **instructions)
{
	t_lab	*last_lab;
	t_instr	*last_op;
	int		op_number;

	init_env(labels, &last_lab, instructions, &last_op);
	op_number = 0;
	while (token->type != END)
	{
		push_labels(&token, &last_lab, op_number);
		push_instruction(&token, &last_op);
		op_number++;
		while (token->type == ENDLINE || token->type == COMMENT)
			token = token->next;
		if (token->type != END)
		{
			last_op->next = ft_memalloc(sizeof(t_instr));
			last_op = last_op->next;
			init_label(&last_lab, op_number);
			init_instruction(&last_op, op_number);
		}
	}
}
