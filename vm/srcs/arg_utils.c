/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juazouz <juazouz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 17:22:24 by juazouz           #+#    #+#             */
/*   Updated: 2019/03/19 16:19:11 by juazouz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	Returns the size of the specified argument type as present in the corewar
**	bytecode.
*/

int			sizeof_arg_type(t_arg_type type)
{
	if (type == REG_CODE)
		return (1);
	if (type == DIR_CODE)
		return (sizeof(t_dir));
	if (type == IND_CODE)
		return (sizeof(t_ind));
	return (0);
}

t_bool		is_valid_reg(int reg_id)
{
	return (reg_id <= REG_NUMBER && reg_id >= 1);
}

static void	convert_endian_size(void *ptr, int size)
{
	int			i;
	int			swap;

	if (!LITTLE_ENDIAN)
		return ;
	i = 0;
	while (i < size / 2)
	{
		swap = ((char*)ptr)[i];
		((char*)ptr)[i] = ((char*)ptr)[size - i - 1];
		((char*)ptr)[size - i - 1] = swap;
		i++;
	}
}

void		param_at(t_instruction *inst, int pos, t_arg_type type, void *res)
{
	int			size;

	size = sizeof_arg_type(type);
	ft_memcpy(res, &inst->param.multi.parameters[pos], size);
	convert_endian_size(res, size);
}
