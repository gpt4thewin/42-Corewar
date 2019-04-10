/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_alive.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juazouz <juazouz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 19:24:52 by agoulas           #+#    #+#             */
/*   Updated: 2019/04/10 18:15:40 by juazouz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	verbose_print_process_count(t_corewar *corewar, int process_count)
{
	if (corewar->arguments.verbosity & VERBOSE_PROCESS_COUNT)
		ft_printf("Cycle %6d | Process count : %d (-%-d process killed)\n",
			corewar->curr_cycle,
			corewar->process_count,
			process_count - corewar->process_count);
}

static void	verbose_print_process_kill(t_corewar *corewar, t_process *process)
{
	if (corewar->arguments.verbosity & VERBOSE_DEATH)
		ft_printf("Cycle %6d | Killing process %d (CTD %d)\n",
			corewar->curr_cycle, process->id, corewar->cycle_to_die);
}

int			kill_dead_process(t_corewar *corewar)
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
			verbose_print_process_kill(corewar, process);
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

void		check_alive(t_corewar *corewar)
{
	int			total_nbr_live;
	t_bool		max_checks_reached;
	int			process_count;

	process_count = corewar->process_count;
	total_nbr_live = kill_dead_process(corewar);
	if (process_count != corewar->process_count)
		verbose_print_process_count(corewar, process_count);
	max_checks_reached = (corewar->checks_count >= MAX_CHECKS);
	if (max_checks_reached || total_nbr_live > NBR_LIVE)
	{
		if (corewar->arguments.verbosity & VERBOSE_CDT)
		{
			ft_printf("Cycle %6d | Decrementing CTD to %d%s\n",
				corewar->curr_cycle, corewar->cycle_to_die,
				max_checks_reached ? " (MAX_CHECKS reached)" : "");
		}
		corewar->checks_count = 0;
		if (corewar->cycle_to_die <= CYCLE_DELTA)
			corewar->cycle_to_die = 0;
		else
			corewar->cycle_to_die -= CYCLE_DELTA;
	}
	corewar->checks_count++;
}
