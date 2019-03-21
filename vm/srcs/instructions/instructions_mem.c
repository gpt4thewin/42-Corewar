/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions_mem.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juazouz <juazouz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 16:37:53 by juazouz           #+#    #+#             */
/*   Updated: 2019/03/21 17:58:30 by juazouz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	inst_ld(t_corewar *corewar, t_process *process, t_paraminfo *param)
{
	t_memaccess	memaccess;
	int			val;

	memaccess.idxmod = true;
	memaccess.process = process;
	memaccess.value_size = REG_SIZE;
	val = generic_read(corewar, &memaccess, param->params[0]);
	process->reg[(int)param->params[1].value.reg_id - 1] = val;
	process->carry = (memaccess._value == 0);
}

void	inst_st(t_corewar *corewar, t_process *process, t_paraminfo *param)
{
	t_memaccess	memaccess;
	int			val;

	memaccess.idxmod = true;
	val = process->reg[(int)param->params[0].value.reg_id - 1];
	memaccess.process = process;
	memaccess.value_size = REG_SIZE;
	generic_write(corewar, &memaccess, param->params[1], val);
}

void	inst_ldi(t_corewar *corewar, t_process *process, t_paraminfo *param)
{
	t_memaccess	memaccess;
	int			val;
	int			reg_id;
	t_param		sum_param;

	memaccess.idxmod = true;
	memaccess.process = process;
	memaccess.value_size = REG_SIZE;
	sum_param.value.ind = generic_read(corewar, &memaccess, param->params[0]);
	sum_param.value.ind += generic_read(corewar, &memaccess, param->params[1]);
	sum_param.type = IND_CODE;
	reg_id = param->params[2].value.reg_id;
	val = generic_read(corewar, &memaccess, sum_param);
	process_set_reg(process, reg_id, val);
	process->carry = (val == 0);
}

void	inst_sti(t_corewar *corewar, t_process *process, t_paraminfo *param)
{
	t_memaccess	memaccess;
	int			reg_id;
	int			val;
	t_param		sum_param;

	reg_id = param->params[0].value.reg_id;
	val = process_get_reg(process, reg_id);
	memaccess.idxmod = true;
	memaccess.process = process;
	memaccess.value_size = REG_SIZE;
	sum_param.value.ind = generic_read(corewar, &memaccess, param->params[1]);
	sum_param.value.ind += generic_read(corewar, &memaccess, param->params[2]);
	sum_param.type = IND_CODE;
	generic_write(corewar, &memaccess, sum_param, val);
}
