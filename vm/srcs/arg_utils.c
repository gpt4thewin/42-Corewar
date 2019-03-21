/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juazouz <juazouz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 17:22:24 by juazouz           #+#    #+#             */
/*   Updated: 2019/03/21 13:28:15 by juazouz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	Returns the size of the specified argument type as present in the corewar
**	bytecode.
*/

int			sizeof_param_type(t_arg_type type, t_bool has_size_mod)
{
	if (type == REG_CODE)
		return (1);
	if (type == DIR_CODE)
	{
		if (!has_size_mod)
			return (sizeof(t_dir));
		return (sizeof(t_ind));
	}
	if (type == IND_CODE)
		return (sizeof(t_ind));
	return (0);
}

t_bool		is_valid_reg(int reg_id)
{
	return (reg_id <= REG_NUMBER && reg_id >= 1);
}
