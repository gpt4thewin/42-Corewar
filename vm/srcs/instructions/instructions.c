/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juazouz <juazouz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 14:52:44 by juazouz           #+#    #+#             */
/*   Updated: 2019/03/14 13:44:41 by juazouz          ###   ########.fr       */
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
	t_reg			reg_id;
	int				i;

	reg_id = inst->param.single_reg;
	if (is_valid_reg(reg_id))
	{
		player_id = get_reg_value(process, reg_id);
		i = 0;
		while (i < corewar->players_count)
		{
			if (corewar->players[i].id == player_id)
			{
				corewar->last_live = &corewar->players[i];
				ft_printf("Le joueur %d(%s) est en vie.\n",
					corewar->players[i].id,
					&corewar->players[i].prog_name);
				break ;
			}
			i++;
		}
	}
	return (2);
}

int	inst_ld(t_corewar *corewar, t_process *process, t_instruction *inst)
{
	// t_instruction	*inst;

	// inst = process->pc;
	// // Passer l'instruction ?
	// // if (inst->param.multi.arg_type_2 != T_REG)
	// // 	return (1);
	// if (inst->param.multi.arg_type_1 == T_DIR)
	// {

	// }
	(void)inst;
	(void)corewar;
	(void)process;
	return (1);
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
