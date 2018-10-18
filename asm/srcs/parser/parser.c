/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbakhti <mbakhti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 15:14:52 by mbakhti           #+#    #+#             */
/*   Updated: 2019/03/08 19:14:24 by mbakhti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	free_env(t_lab **labels, t_instr **instructions, t_token **tokens)
{
	t_lab	*tmp_lab;
	t_instr	*tmp_ins;
	t_token	*tmp_tok;

	while (*labels)
	{
		tmp_lab = *labels;
		*labels = (*labels)->next;
		free(tmp_lab);
	}
	while (*instructions)
	{
		tmp_ins = *instructions;
		*instructions = (*instructions)->next;
		free(tmp_ins);
	}
	while (*tokens)
	{
		tmp_tok = *tokens;
		*tokens = (*tokens)->next;
		free(tmp_tok->value);
		free(tmp_tok);
	}
}

static void	init_bytecode(t_bytecode *bytecode)
{
	bytecode->header.magic = COREWAR_EXEC_MAGIC;
	ft_bzero(bytecode->header.prog_name, PROG_NAME_LENGTH + 1);
	ft_bzero(bytecode->header.comment, COMMENT_LENGTH + 1);
	if (!(bytecode->program = ft_strnew(0)))
		ft_exit_error("error: can't malloc");
}

void		parse_tokens(t_bytecode *bytecode, t_token *tokens)
{
	t_token	*current;
	t_lab	*labels;
	t_instr	*instructions;

	current = tokens;
	init_bytecode(bytecode);
	generate_header(&bytecode->header, &current);
	check_syntax(current, &labels, &instructions);
	generate_program(bytecode, &labels, &instructions);
	free_env(&labels, &instructions, &tokens);
}
