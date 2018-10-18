/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_program.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbakhti <mbakhti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 18:37:50 by mbakhti           #+#    #+#             */
/*   Updated: 2019/03/08 19:14:23 by mbakhti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	get_param(t_instr *op, int i, t_instr **instructions, t_lab *labels)
{
	if (op->param[i].type == REGISTER)
		op->arg[i] = ft_atoi(&op->param[i].value[1]);
	else if (op->param[i].type == INDIRECT)
		op->arg[i] = ft_atoi(op->param[i].value);
	else if (op->param[i].type == DIRECT)
		op->arg[i] = ft_atoi(&op->param[i].value[1]);
	else if (op->param[i].type == INDIRECT_LABEL)
		op->arg[i] = get_label_offset(&op->param[i].value[1], labels)
		- get_current_offset(*op, *instructions);
	else if (op->param[i].type == DIRECT_LABEL)
		op->arg[i] = get_label_offset(&op->param[i].value[2], labels)
		- get_current_offset(*op, *instructions);
}

static void	resolve_param(t_instr **instructions, t_lab *labels)
{
	t_instr	*op_ptr;
	int		i;

	op_ptr = *instructions;
	while (op_ptr)
	{
		i = 0;
		while (i < MAX_ARGS_NUMBER && op_ptr->param[i].type)
		{
			get_param(op_ptr, i, instructions, labels);
			i++;
		}
		op_ptr = op_ptr->next;
	}
}

static void	resolve_labels(t_lab **labels, t_instr *instructions)
{
	t_lab	*lab_ptr;
	t_instr	*op_ptr;

	lab_ptr = *labels;
	while (lab_ptr)
	{
		op_ptr = instructions;
		while (op_ptr->op_number < lab_ptr->op_number)
		{
			lab_ptr->offset += op_ptr->size;
			op_ptr = op_ptr->next;
		}
		lab_ptr = lab_ptr->next;
	}
}

void		generate_program(t_bytecode *bytecode, t_lab **labels,
t_instr **instructions)
{
	check_instructions(instructions, *labels);
	resolve_labels(labels, *instructions);
	resolve_param(instructions, *labels);
	write_instructions(bytecode, *instructions);
}
