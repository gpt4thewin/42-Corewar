/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_alive.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juazouz <juazouz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 19:24:52 by agoulas           #+#    #+#             */
/*   Updated: 2019/03/29 16:05:47 by juazouz          ###   ########.fr       */
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
			if (corewar->arguments.verbosity & VERBOSE_DEATH)
				ft_printf("Killing process %d (CTD %d)\n",
					process->id, corewar->cycle_to_die);
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
	int			total_nbr_live;

	total_nbr_live = kill_dead_process(corewar);
	if (corewar->checks_count >= MAX_CHECKS || total_nbr_live > NBR_LIVE)
	{
		if (corewar->arguments.verbosity & VERBOSE_CDT)
			ft_printf("Decrementing CDT to %d\n", corewar->cycle_to_die);
		corewar->checks_count = 0;
		if (corewar->cycle_to_die <= CYCLE_DELTA)
			corewar->cycle_to_die = 0;
		else
			corewar->cycle_to_die -= CYCLE_DELTA;
	}
	corewar->checks_count++;
}
