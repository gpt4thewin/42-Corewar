/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_instructions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbakhti <mbakhti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 15:32:33 by mbakhti           #+#    #+#             */
/*   Updated: 2019/03/09 04:12:26 by mbakhti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	write_four_bytes(char *program, int *offset, char buffer[4])
{
	program[*offset] = buffer[0];
	program[*offset + 1] = buffer[1];
	program[*offset + 2] = buffer[2];
	program[*offset + 3] = buffer[3];
	*offset += 4;
}

static void	write_two_bytes(char *program, int *offset, char buffer[4])
{
	program[*offset] = buffer[2];
	program[*offset + 1] = buffer[3];
	*offset += 2;
}

static void	get_buffer(char buffer[4], t_instr *op, int i)
{
	buffer[0] = (op->arg[i] & 0xff000000) >> 24;
	buffer[1] = (op->arg[i] & 0x00ff0000) >> 16;
	buffer[2] = (op->arg[i] & 0x0000ff00) >> 8;
	buffer[3] = (op->arg[i] & 0x000000ff);
}

static void	write_parameters(char *program, t_instr *instructions)
{
	int		i;
	int		offset;
	t_instr	*op_ptr;
	char	buffer[4];

	i = 0;
	offset = 0;
	op_ptr = instructions;
	while (i < MAX_ARGS_NUMBER && op_ptr->param[i].type)
	{
		get_buffer(buffer, op_ptr, i);
		if (get_type_size(&op_ptr, i) == 1)
		{
			program[offset] = buffer[3];
			offset += 1;
		}
		else if (get_type_size(&op_ptr, i) == 2)
			write_two_bytes(program, &offset, buffer);
		else if (get_type_size(&op_ptr, i) == 4)
			write_four_bytes(program, &offset, buffer);
		i++;
	}
}

void		write_instructions(t_bytecode *bytecode, t_instr *instructions)
{
	int		size;
	t_instr	*op_ptr;
	char	*prog;

	size = 0;
	op_ptr = instructions;
	while (op_ptr)
	{
		size += op_ptr->size;
		if (!(bytecode->program = realloc(bytecode->program,
		sizeof(char) * size + 1)))
			ft_exit_error("error: can't realloc");
		prog = &bytecode->program[size - op_ptr->size];
		ft_bzero(prog, op_ptr->size);
		*prog = op_ptr->opcode;
		prog++;
		if (op_ptr->opcode && g_op_tab[op_ptr->opcode - 1].has_argcode)
		{
			*prog = op_ptr->argcode;
			prog++;
		}
		write_parameters(prog, op_ptr);
		op_ptr = op_ptr->next;
	}
	bytecode->header.prog_size = size;
}
