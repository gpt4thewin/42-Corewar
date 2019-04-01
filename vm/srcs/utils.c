/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juazouz <juazouz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 14:41:00 by juazouz           #+#    #+#             */
/*   Updated: 2019/04/01 15:44:38 by juazouz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	Converts an address into a physical address for the circular memory.
*/

int				get_physical_addr(int addr)
{
	int	res;

	res = addr;
	if (res < 0)
	{
		res += MEM_SIZE;
		res += (-addr / MEM_SIZE) * MEM_SIZE;
	}
	return (res % MEM_SIZE);
}

/*
**	Returns the t_op data related to the specified opcode.
*/

t_op			*get_op(int opcode)
{
	t_op	*res;

	if (opcode >= OP_TAB_SIZE || opcode < 1)
		return (NULL);
	res = &g_op_tab[opcode - 1];
	return (res);
}

/*
**	Returns the size of the specified argument type as present in the corewar
**	bytecode.
*/

int				sizeof_param_type(t_arg_type type)
{
	if (type == REG_CODE)
		return (1);
	if (type == DIR_CODE)
		return (sizeof(t_dir));
	if (type == IND_CODE || type == DIR_MOD_CODE)
		return (sizeof(t_ind));
	return (0);
}

t_bool			is_valid_reg(int reg_id)
{
	return (reg_id <= REG_NUMBER && reg_id >= 1);
}
