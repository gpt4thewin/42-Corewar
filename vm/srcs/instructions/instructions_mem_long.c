/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions_mem_long.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juazouz <juazouz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 16:38:41 by juazouz           #+#    #+#             */
/*   Updated: 2019/03/26 18:59:15 by juazouz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	inst_lld(t_corewar *corewar, t_process *process, t_paraminfo *param)
{
	t_memaccess	memaccess;
	int			val;

	memaccess.idxmod = false;
	memaccess.process = process;
	memaccess.value_size = REG_SIZE;
	val = generic_read(corewar, &memaccess, param->params[0]);
	process_set_reg(process, param->params[1].value.reg_id, val);
	process->carry = (memaccess._value == 0);
}

void	inst_lldi(t_corewar *corewar, t_process *process, t_paraminfo *param)
{
	t_memaccess	memaccess;
	int			val;
	int			reg_id;
	t_param		sum_param;

	memaccess.idxmod = false;
	memaccess.process = process;
	memaccess.value_size = DIR_SIZE;
	sum_param.value.ind = generic_read(corewar, &memaccess, param->params[0]);
	sum_param.value.ind += generic_read(corewar, &memaccess, param->params[1]);
	sum_param.type = IND_CODE;
	reg_id = param->params[2].value.reg_id;
	memaccess.value_size = REG_SIZE;
	val = generic_read(corewar, &memaccess, sum_param);
	process_set_reg(process, reg_id, val);
	process->carry = (val == 0);
}
