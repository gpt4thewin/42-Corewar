/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juazouz <juazouz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 15:57:25 by juazouz           #+#    #+#             */
/*   Updated: 2019/03/19 16:35:03 by juazouz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int	((*g_op_func_tab[])(t_corewar*, t_process*, t_instruction*)) =
{
	NULL,
	inst_live,
	inst_ld,
	inst_st,
	inst_add,
	inst_sub,
	inst_and,
	inst_or,
	inst_xor,
	inst_zjmp,
	inst_ldi,
	inst_sti,
	inst_fork,
	inst_lld,
	inst_lldi,
	inst_lfork,
	inst_aff,
};

int	inst_live(t_corewar *corewar, t_process *process, t_instruction *inst)
{
	int				player_id;
	int				i;

	player_id = inst->param.single_dir;
	i = 0;
	while (i < corewar->players_count)
	{
		if (corewar->players[i].id == player_id)
		{
			corewar->last_live = &corewar->players[i];
			process->nbr_live++;
			ft_printf("Le joueur %d(%s) est en vie.\n",
				corewar->players[i].id,
				&corewar->players[i].prog_name);
			break ;
		}
		i++;
	}
	return (2);
}

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
	(void)inst;
	(void)corewar;
	(void)process;
	return (1);
}

int	inst_add(t_corewar *corewar, t_process *process, t_instruction *inst)
{
	(void)inst;
	(void)corewar;
	(void)process;
	return (1);
}

int	inst_sub(t_corewar *corewar, t_process *process, t_instruction *inst)
{
	(void)inst;
	(void)corewar;
	(void)process;
	return (1);
}

int	inst_and(t_corewar *corewar, t_process *process, t_instruction *inst)
{
	(void)inst;
	(void)corewar;
	(void)process;
	return (1);
}

int	inst_or(t_corewar *corewar, t_process *process, t_instruction *inst)
{
	(void)inst;
	(void)corewar;
	(void)process;
	return (1);
}

int	inst_xor(t_corewar *corewar, t_process *process, t_instruction *inst)
{
	(void)inst;
	(void)corewar;
	(void)process;
	return (1);
}

int	inst_zjmp(t_corewar *corewar, t_process *process, t_instruction *inst)
{
	(void)inst;
	(void)corewar;
	(void)process;
	return (1);
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

int	inst_fork(t_corewar *corewar, t_process *process, t_instruction *inst)
{
	(void)inst;
	(void)corewar;
	(void)process;
	return (1);
}

int	inst_lld(t_corewar *corewar, t_process *process, t_instruction *inst)
{
	(void)inst;
	(void)corewar;
	(void)process;
	return (1);
}

int	inst_lldi(t_corewar *corewar, t_process *process, t_instruction *inst)
{
	(void)inst;
	(void)corewar;
	(void)process;
	return (1);
}

int	inst_lfork(t_corewar *corewar, t_process *process, t_instruction *inst)
{
	(void)inst;
	(void)corewar;
	(void)process;
	return (1);
}

int	inst_aff(t_corewar *corewar, t_process *process, t_instruction *inst)
{
	(void)inst;
	(void)corewar;
	(void)process;
	return (1);
}
