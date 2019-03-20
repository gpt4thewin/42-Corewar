/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions_core.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juazouz <juazouz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 15:57:25 by juazouz           #+#    #+#             */
/*   Updated: 2019/03/20 17:30:05 by juazouz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	((*g_op_func_tab[])(t_corewar*, t_process*, t_paraminfo*)) =
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

void	inst_live(t_corewar *corewar, t_process *process, t_paraminfo *param)
{
	int				player_id;
	int				i;

	player_id = param->params[0].value.dir;
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
}

void	inst_zjmp(t_corewar *corewar, t_process *process, t_paraminfo *param)
{
	(void)param;
	(void)corewar;
	(void)process;
}

void	inst_fork(t_corewar *corewar, t_process *process, t_paraminfo *param)
{
	(void)param;
	(void)corewar;
	(void)process;
}

void	inst_lfork(t_corewar *corewar, t_process *process, t_paraminfo *param)
{
	(void)param;
	(void)corewar;
	(void)process;
}

void	inst_aff(t_corewar *corewar, t_process *process, t_paraminfo *param)
{
	(void)param;
	(void)corewar;
	(void)process;
}
