/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juazouz <juazouz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 18:20:52 by mbakhti           #+#    #+#             */
/*   Updated: 2019/04/01 14:00:28 by juazouz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		get_type_size(t_instr **op, int i)
{
	if ((*op)->param[i].type == REGISTER)
		return (1);
	else if ((*op)->param[i].type == INDIRECT
	|| (*op)->param[i].type == INDIRECT_LABEL)
		return (2);
	else if ((*op)->param[i].type == DIRECT
	|| (*op)->param[i].type == DIRECT_LABEL)
	{
		if (g_op_tab[(*op)->opcode - 1].has_size_mod)
			return (2);
		return (4);
	}
	return (0);
}

int		get_current_offset(t_instr current, t_instr *instructions)
{
	int		offset;
	t_instr	*op_ptr;

	offset = 0;
	op_ptr = instructions;
	while (op_ptr->op_number < current.op_number)
	{
		offset += op_ptr->size;
		op_ptr = op_ptr->next;
	}
	return (offset);
}

int		get_label_offset(char *label_name, t_lab *labels)
{
	t_lab	*lab_ptr;

	lab_ptr = labels;
	while (lab_ptr)
	{
		if (ft_strequ(label_name, lab_ptr->label.value))
			return (lab_ptr->offset);
		lab_ptr = lab_ptr->next;
	}
	return (0);
}

void	copy_token(t_token src, t_token *dst)
{
	dst->type = src.type;
	dst->value = src.value;
	dst->position = src.position;
	dst->next = NULL;
}

void	display_faulty_token(t_token token)
{
	char *name[14];

	name[0] = "END";
	name[1] = "ENDLINE";
	name[2] = "WHITESPACE";
	name[3] = "SEPARATOR";
	name[4] = "COMMENT";
	name[5] = "COMMAND";
	name[6] = "STRING";
	name[7] = "LABEL";
	name[8] = "REGISTER";
	name[9] = "INDIRECT";
	name[10] = "INDIRECT_LABEL";
	name[11] = "DIRECT";
	name[12] = "DIRECT_LABEL";
	name[13] = "INSTRUCTION";
	ft_fprintf(2, " [TOKEN][%03d:%03d] %s",
	token.position.lin, token.position.col, name[token.type]);
	if (token.type != ENDLINE)
		ft_fprintf(2, " \"%s\"\n", token.value);
	else
		ft_fprintf(2, "\n");
}
