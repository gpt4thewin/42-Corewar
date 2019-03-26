/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_dead_or_live.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoulas <agoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 19:24:52 by agoulas           #+#    #+#             */
/*   Updated: 2019/03/22 19:25:26 by agoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		kill_dead_process(t_corewar *corewar)
{
	t_process	*process;
	int			total_nbr_live;
	t_list		**curr;

	total_nbr_live = 0;
	curr = &corewar->processes;
	while (*curr != NULL)
	{
		process = (t_process*)(*curr)->content;
		if (process->nbr_live <= 0)
		{
			ft_lstdelone(curr, NULL);
			corewar->process_count--;
		}
		else
		{
			total_nbr_live += process->nbr_live;
			process->nbr_live = 0;
			curr = &(*curr)->next;
		}
	}
	return (total_nbr_live);
}

void	check_alive(t_corewar *corewar)
{
	t_bool		force_check;
	int			total_nbr_live;

	total_nbr_live = kill_dead_process(corewar);
	if (corewar->checks_count >= MAX_CHECKS)
	{
		corewar->checks_count = 0;
		force_check = true;
	}
	else
	{
		force_check = false;
	}
	if (force_check || total_nbr_live > NBR_LIVE)
	{
		if (corewar->cycle_to_die <= CYCLE_DELTA)
			corewar->cycle_to_die = 0;
		else
			corewar->cycle_to_die -= CYCLE_DELTA;
	}
	corewar->checks_count++;
}
