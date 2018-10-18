/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_instructions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbakhti <mbakhti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 13:30:17 by mbakhti           #+#    #+#             */
/*   Updated: 2019/03/09 16:35:38 by mbakhti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char	get_code(t_token_type param_type)
{
	if (param_type == REGISTER)
		return (REG_CODE);
	else if (param_type == DIRECT || param_type == DIRECT_LABEL)
		return (DIR_CODE);
	else if (param_type == INDIRECT || param_type == INDIRECT_LABEL)
		return (IND_CODE);
	return (0);
}

static void	get_argcode(t_instr **op)
{
	int		i;
	char	code[MAX_ARGS_NUMBER];

	if (!g_op_tab[(*op)->opcode - 1].has_argcode)
		return ;
	(*op)->size++;
	i = 0;
	ft_bzero(code, MAX_ARGS_NUMBER);
	while (i < g_op_tab[(*op)->opcode - 1].args_number)
	{
		code[i] = get_code((*op)->param[i].type);
		i++;
	}
	(code[0] == REG_CODE) ? ((*op)->argcode |= 0b01000000) : (0);
	(code[0] == IND_CODE) ? ((*op)->argcode |= 0b11000000) : (0);
	(code[0] == DIR_CODE) ? ((*op)->argcode |= 0b10000000) : (0);
	(code[1] == REG_CODE) ? ((*op)->argcode |= 0b00010000) : (0);
	(code[1] == IND_CODE) ? ((*op)->argcode |= 0b00110000) : (0);
	(code[1] == DIR_CODE) ? ((*op)->argcode |= 0b00100000) : (0);
	(code[2] == REG_CODE) ? ((*op)->argcode |= 0b00000100) : (0);
	(code[2] == IND_CODE) ? ((*op)->argcode |= 0b00001100) : (0);
	(code[2] == DIR_CODE) ? ((*op)->argcode |= 0b00001000) : (0);
	(code[3] == REG_CODE) ? ((*op)->argcode |= 0b00000001) : (0);
	(code[3] == IND_CODE) ? ((*op)->argcode |= 0b00000011) : (0);
	(code[3] == DIR_CODE) ? ((*op)->argcode |= 0b00000010) : (0);
}

static void	check_opcode(t_instr **op)
{
	int		i;

	i = 0;
	while (g_op_tab[i].opcode)
	{
		if (ft_strequ((*op)->op.value, g_op_tab[i].opname))
		{
			(*op)->opcode = g_op_tab[i].opcode;
			(*op)->size++;
			return ;
		}
		i++;
	}
	invalid_instruction_error((*op)->op);
}

void		check_instructions(t_instr **instructions, t_lab *labels)
{
	t_instr	*op_ptr;

	op_ptr = *instructions;
	while (op_ptr)
	{
		if (op_ptr->op.value)
		{
			check_opcode(&op_ptr);
			check_parameters(&op_ptr, labels);
			get_argcode(&op_ptr);
		}
		op_ptr = op_ptr->next;
	}
}
