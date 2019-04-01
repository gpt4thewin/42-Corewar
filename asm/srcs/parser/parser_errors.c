/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juazouz <juazouz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 13:47:09 by mbakhti           #+#    #+#             */
/*   Updated: 2019/04/01 13:59:45 by juazouz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	syntax_error(t_token token)
{
	ft_fprintf(2, "Syntax error at token");
	display_faulty_token(token);
	exit(EXIT_FAILURE);
}

void	invalid_instruction_error(t_token token)
{
	ft_fprintf(2, "Invalid instruction at token");
	display_faulty_token(token);
	exit(EXIT_FAILURE);
}

void	invalid_parameter_error(int i, t_instr op)
{
	char	*type;

	if (op.param[i].type == REGISTER)
		type = "register";
	else if (op.param[i].type == DIRECT
		|| op.param[i].type == DIRECT_LABEL)
		type = "direct";
	else if (op.param[i].type == INDIRECT
		|| op.param[i].type == INDIRECT_LABEL)
		type = "indirect";
	else
		type = "";
	ft_fprintf(2, "Invalid parameter %d type %s for instruction %s\n",
		i, type, op.op.value);
	exit(EXIT_FAILURE);
}

void	invalid_label_error(char *label, t_token token)
{
	ft_fprintf(2, "No such label %s while attempting to dereference token",
		label);
	display_faulty_token(token);
	exit(EXIT_FAILURE);
}

void	invalid_parameter_count(t_instr op)
{
	ft_fprintf(2, "Invalid parameter count for instruction %s\n", op.op.value);
	exit(EXIT_FAILURE);
}
