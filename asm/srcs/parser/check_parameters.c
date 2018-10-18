/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parameters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbakhti <mbakhti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 13:31:21 by mbakhti           #+#    #+#             */
/*   Updated: 2019/03/08 19:14:10 by mbakhti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	check_label(t_token param, t_lab *labels)
{
	char	*label;
	t_lab	*lab_ptr;

	if (param.type == DIRECT_LABEL)
		label = &param.value[2];
	if (param.type == INDIRECT_LABEL)
		label = &param.value[1];
	lab_ptr = labels;
	while (lab_ptr)
	{
		if (ft_strequ(label, lab_ptr->label.value))
			return ;
		lab_ptr = lab_ptr->next;
	}
	invalid_label_error(label, param);
}

static char	get_type(t_token_type tok_type)
{
	if (tok_type == REGISTER)
		return (T_REG);
	if (tok_type == DIRECT || tok_type == DIRECT_LABEL)
		return (T_DIR);
	if (tok_type == INDIRECT || tok_type == INDIRECT_LABEL)
		return (T_IND);
	return (0);
}

static int	check_parameter_count(t_instr **op)
{
	int		i;

	i = 0;
	while (i < MAX_ARGS_NUMBER && (*op)->param[i].type)
		i++;
	if (i != g_op_tab[(*op)->opcode - 1].args_number)
		invalid_parameter_count(**op);
	return (i);
}

void		check_parameters(t_instr **op, t_lab *labels)
{
	int		i;
	int		size;

	i = 0;
	size = check_parameter_count(op);
	while (i < size)
	{
		if (!(get_type((*op)->param[i].type)
		& g_op_tab[(*op)->opcode - 1].args[i]))
			invalid_parameter_error(i, **op);
		if ((*op)->param[i].type == DIRECT_LABEL
		|| (*op)->param[i].type == INDIRECT_LABEL)
			check_label((*op)->param[i], labels);
		(*op)->size += get_type_size(op, i);
		i++;
	}
}
