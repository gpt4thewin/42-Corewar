/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_params.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juazouz <juazouz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 15:56:51 by juazouz           #+#    #+#             */
/*   Updated: 2019/03/29 13:42:51 by juazouz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static t_bool	type_allowed(t_op *op, t_arg_type type, int index)
{
	return (type != 0 && op->args[index] & (0x1 << (type - 1)));
}

static t_bool	load_param(t_param *param, size_t *pos, void *ptr)
{
	if (param->type == REG_CODE)
	{
		param->value.reg_id = *((char*)ptr + (*pos));
		if (!is_valid_reg(param->value.reg_id))
			return (false);
		(*pos) += sizeof(char);
	}
	else if (param->type == DIR_CODE)
	{
		ft_memcpy(&param->value.ind, ptr + (*pos), sizeof(t_dir));
		param->value.dir = convert_endian32(param->value.dir);
		(*pos) += sizeof(t_dir);
	}
	else if (param->type == IND_CODE || param->type == DIR_MOD_CODE)
	{
		ft_memcpy(&param->value.ind, ptr + (*pos), sizeof(t_ind));
		param->value.ind = convert_endian16(param->value.ind);
		(*pos) += sizeof(t_ind);
	}
	else
		return (false);
	return (true);
}

t_bool			load_params(t_op *op, t_instruction *inst, t_paraminfo *paraminfo)
{
	int					i;
	size_t				pos;
	char				types;
	struct s_inst_param	*multi;
	t_arg_type			type;

	pos = 0;
	ft_bzero(paraminfo, sizeof(t_paraminfo));
	if (!op->has_argcode)
	{
		paraminfo->args_number = 1;
		if (op->has_size_mod)
			paraminfo->params[0].type = DIR_MOD_CODE;
		else
			paraminfo->params[0].type = DIR_CODE;
		load_param(&paraminfo->params[0], &pos, &inst->param.single_dir);
		return (true);
	}
	multi = &inst->param.multi;
	types = *((char*)&inst->param.multi);
	i = 0;
	while (i < op->args_number)
	{
		paraminfo->params[i].type = ((types << (2 * i)) & 0xc0) >> 6;
		if (!type_allowed(op, paraminfo->params[i].type, i))
			return (false);
		if (op->has_size_mod && paraminfo->params[i].type == DIR_CODE)
			paraminfo->params[i].type = DIR_MOD_CODE;
		if (!load_param(&paraminfo->params[i], &pos, &multi->parameters))
			return (false);
		paraminfo->args_number++;
		i++;
	}
	while (i < MAX_ARGS_NUMBER)
	{
		type = types << (2 * i) & 0x03;
		if (type != 0)
			return (false);
		i++;
	}
	return (true);
}
