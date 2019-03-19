/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions_core.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juazouz <juazouz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 15:57:25 by juazouz           #+#    #+#             */
/*   Updated: 2019/03/19 16:42:28 by juazouz          ###   ########.fr       */
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

int	inst_zjmp(t_corewar *corewar, t_process *process, t_instruction *inst)
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
