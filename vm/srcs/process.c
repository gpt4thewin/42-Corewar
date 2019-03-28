/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juazouz <juazouz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 15:12:12 by juazouz           #+#    #+#             */
/*   Updated: 2019/03/28 18:12:33 by juazouz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_process	*process_new(void)
{
	t_process	*res;
	static int	last_id;

	res = ft_memalloc(sizeof(t_process));
	res->exec_cycle = -1;
	res->id = last_id;
	last_id++;
	return (res);
}

t_process	*process_copy(t_process *process)
{
	t_process	*res;
	int			id;

	res = process_new();
	id = res->id;
	ft_memcpy(res, process, sizeof(t_process));
	res->id = id;
	return (res);
}

/*
**	Tries to set the specified registry value.
*/

void		process_set_reg(t_process *process, char reg_id, t_reg val)
{
	if (is_valid_reg(reg_id))
		process->reg[reg_id - 1] = val;
}

/*
**	Tries to read the specified registry value. If reg_id is not valid,
**	returns 0.
*/

t_reg		process_get_reg(t_process *process, char reg_id)
{
	if (!is_valid_reg(reg_id))
		return (0);
	return (process->reg[reg_id - 1]);
}
