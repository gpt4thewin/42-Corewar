/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_params.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juazouz <juazouz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 15:56:51 by juazouz           #+#    #+#             */
/*   Updated: 2019/03/20 16:03:17 by juazouz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static t_bool	type_allowed(t_op *op, t_arg_type type, int index)
{
	return (type != 0 && op->args[index] & (0x1 << (type - 1)));
}

static t_bool	load_param(t_arg_type type, size_t *pos, void *ptr,
	t_paramval *val)
{
	t_paramval			res;

	if (type == REG_CODE)
	{
		res.reg_id = *((char*)ptr + (*pos));
		if (!is_valid_reg(res.reg_id))
			return (false);
		(*pos) += sizeof(char);
	}
	else if (type == DIR_CODE)
	{
		res.dir = *((t_dir*)ptr + (*pos));
		res.dir = convert_endian32(res.dir);
		(*pos) += sizeof(t_dir);
	}
	else if (type == IND_CODE)
	{
		res.ind = *((t_dir*)ptr + (*pos));
		res.ind = convert_endian16(res.ind);
		(*pos) += sizeof(t_ind);
	}
	else
		return (false);
	*val = res;
	return (true);
}

t_bool			load_params(t_op *op, t_instruction *inst, t_paraminfo *paraminfo)
{
	int				i;
	size_t			pos;
	char			types;
	struct s_param	*multi;
	t_arg_type		type;

	ft_bzero(paraminfo, sizeof(t_paraminfo));
	if (!op->has_argcode)
	{
		paraminfo->args_number = 1;
		paraminfo->types[0] = DIR_CODE;
		paraminfo->values[0].dir = inst->param.single_dir;
		return (true);
	}
	multi = &inst->param.multi;
	types = *((char*)&inst->param.multi);
	i = 0;
	pos = 0;
	while (i < op->args_number)
	{
		type = ((types << (2 * i)) & 0xc0) >> 6;
		paraminfo->types[i] = type;
		if (!type_allowed(op, type, i))
			return (false);
		if (!load_param(type, &pos, &multi->parameters, &paraminfo->values[i]))
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
