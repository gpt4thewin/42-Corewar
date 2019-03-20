/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions_mem.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juazouz <juazouz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 16:37:53 by juazouz           #+#    #+#             */
/*   Updated: 2019/03/20 17:51:16 by juazouz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	inst_ld(t_corewar *corewar, t_process *process, t_paraminfo *param)
{
	t_memaccess	memaccess;

	memaccess.idxmod = true;
	memaccess.process = process;
	memaccess.value_size = REG_SIZE;
	memaccess.param = param->params[0];
	generic_read(corewar, &memaccess);
	process->reg[(int)param->params[1].value.reg_id - 1] = memaccess.value;
	process->carry = (memaccess.value == 0);
}

void	inst_st(t_corewar *corewar, t_process *process, t_paraminfo *param)
{
	t_memaccess	memaccess;

	memaccess.idxmod = true;
	memaccess.value = process->reg[(int)param->params[0].value.reg_id - 1];
	memaccess.process = process;
	memaccess.value_size = REG_SIZE;
	memaccess.param = param->params[1];
	generic_write(corewar, &memaccess);
}

void	inst_ldi(t_corewar *corewar, t_process *process, t_paraminfo *param)
{
	t_memaccess	memaccess;
	int			sum;

	memaccess.idxmod = true;
	memaccess.process = process;
	memaccess.value_size = REG_SIZE;
	memaccess.param = param->params[0];
	generic_read(corewar, &memaccess);
	sum = memaccess.value;
	sum += param->params[1].value.dir;
	memaccess.param = param->params[2];
}

void	inst_sti(t_corewar *corewar, t_process *process, t_paraminfo *param)
{
	(void)param;
	(void)corewar;
	(void)process;
}
