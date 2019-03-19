/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions_mem.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juazouz <juazouz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 16:37:53 by juazouz           #+#    #+#             */
/*   Updated: 2019/03/19 17:10:07 by juazouz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int	inst_ld(t_corewar *corewar, t_process *process, t_instruction *inst)
{
	t_memaccess	memaccess;
	int			tmp;
	char		reg_id;
	int			arg1_size;

	if (inst->param.multi.arg_type_2 != REG_CODE)
		return (2);
	arg1_size = sizeof_arg_type(memaccess.arg_type);
	memaccess.process = process;
	memaccess.memsize = sizeof(t_reg);
	memaccess.arg_type = inst->param.multi.arg_type_1;
	param_at(inst, 0, inst->param.multi.arg_type_1, &tmp);
	memaccess.paramval = *(t_paramval*)&tmp;
	generic_read(corewar, &memaccess);
	param_at(inst, arg1_size, inst->param.multi.arg_type_1, &reg_id);
	memaccess.arg_type = REG_CODE;
	memaccess.paramval.reg_id = reg_id;
	generic_write(corewar, &memaccess);
	return (2 + sizeof_arg_type(REG_CODE) + arg1_size);
}

int	inst_st(t_corewar *corewar, t_process *process, t_instruction *inst)
{
	t_memaccess	memaccess;
	int			tmp;
	char		reg_id;
	int			arg2_size;

	if (inst->param.multi.arg_type_1 != REG_CODE)
		return (2);
	memaccess.process = process;
	memaccess.memsize = sizeof(t_reg);
	memaccess.arg_type = REG_CODE;
	param_at(inst, 0, inst->param.multi.arg_type_1, &reg_id);
	memaccess.paramval.reg_id = reg_id;
	generic_read(corewar, &memaccess);
	if (memaccess.success)
	{
		memaccess.arg_type = inst->param.multi.arg_type_2;
		memaccess.memsize = sizeof(t_reg);
		param_at(inst, sizeof_arg_type(REG_CODE), memaccess.arg_type, &tmp);
		memaccess.paramval = *(t_paramval*)&tmp;
		generic_write(corewar, &memaccess);
	}
	arg2_size = sizeof_arg_type(memaccess.arg_type);
	return (2 + sizeof_arg_type(REG_CODE) + arg2_size);
}

int	inst_ldi(t_corewar *corewar, t_process *process, t_instruction *inst)
{
	(void)inst;
	(void)corewar;
	(void)process;
	return (1);
}

int	inst_sti(t_corewar *corewar, t_process *process, t_instruction *inst)
{
	(void)inst;
	(void)corewar;
	(void)process;
	return (1);
}
