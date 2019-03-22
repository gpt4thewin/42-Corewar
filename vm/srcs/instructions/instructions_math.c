/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions_math.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoulas <agoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 16:36:26 by juazouz           #+#    #+#             */
/*   Updated: 2019/03/22 18:26:42 by agoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	inst_and_or_xor(t_corewar *corewar, t_process *process,
	t_paraminfo *param, int type)
{
	t_memaccess	memaccess;
	int			val1;
	int			val2;
	int			res;
	int			reg_id;

	memaccess.idxmod = true;
	memaccess.process = process;
	memaccess.value_size = DIR_SIZE;
	val1 = generic_read(corewar, &memaccess, param->params[0]);
	val2 = generic_read(corewar, &memaccess, param->params[1]);
	if (type < 0 || type > 2)
		corewar_die("instruction inconnue");
	if (type == 0)
		res = val1 & val2;
	else
		res = (type == 1) ? (val1 | val2) : (val1 ^ val2);
	reg_id = param->params[2].value.reg_id;
	process_set_reg(process, reg_id, res);
	process->carry = (res == 0);
}

void		inst_and(t_corewar *corewar, t_process *process, t_paraminfo *param)
{
	inst_and_or_xor(corewar, process, param, 0);
}

void		inst_or(t_corewar *corewar, t_process *process, t_paraminfo *param)
{
	inst_and_or_xor(corewar, process, param, 1);
}

void		inst_xor(t_corewar *corewar, t_process *process, t_paraminfo *param)
{
	inst_and_or_xor(corewar, process, param, 2);
}
