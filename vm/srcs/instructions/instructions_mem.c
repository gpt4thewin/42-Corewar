/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions_mem.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juazouz <juazouz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 16:37:53 by juazouz           #+#    #+#             */
/*   Updated: 2019/03/20 17:14:05 by juazouz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	inst_ld(t_corewar *corewar, t_process *process, t_paraminfo *param)
{
	t_memaccess	memaccess;

	memaccess.idxmod = true;
	memaccess.process = process;
	memaccess.value_size = REG_SIZE;
	memaccess.param_type = param->types[0];
	memaccess.param_val = param->values[0];
	generic_read(corewar, &memaccess);
	process->reg[(int)param->values[1].reg_id - 1] = memaccess.value;
	process->carry = (memaccess.value == 0);
}

void	inst_st(t_corewar *corewar, t_process *process, t_paraminfo *param)
{
	t_memaccess	memaccess;

	memaccess.idxmod = true;
	memaccess.value = process->reg[(int)param->values[0].reg_id - 1];
	memaccess.process = process;
	memaccess.value_size = REG_SIZE;
	memaccess.param_type = param->types[1];
	memaccess.param_val = param->values[1];
	generic_write(corewar, &memaccess);
}

void	inst_ldi(t_corewar *corewar, t_process *process, t_paraminfo *param)
{
	(void)param;
	(void)corewar;
	(void)process;
}

void	inst_sti(t_corewar *corewar, t_process *process, t_paraminfo *param)
{
	(void)param;
	(void)corewar;
	(void)process;
}
