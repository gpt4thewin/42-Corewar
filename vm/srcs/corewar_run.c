/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_run.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juazouz <juazouz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 19:23:09 by juazouz           #+#    #+#             */
/*   Updated: 2019/03/22 17:22:48 by juazouz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int			get_params_size(t_paraminfo *paraminfo)
{
	int	i;
	int	res;

	res = 0;
	i = 0;
	while (i < paraminfo->args_number)
	{
		res += sizeof_param_type(paraminfo->params[i].type);
		i++;
	}
	return (res);
}

static t_op			*get_op(int opcode)
{
	t_op	*res;

	if (opcode >= OP_TAB_SIZE || opcode < 1)
		return (NULL);
	res = &g_op_tab[opcode - 1];
	return (res);
}

static int			kill_dead_process(t_corewar *corewar)
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

static void			check_alive(t_corewar *corewar)
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

/*
**	Runs the next instruction of the specified process.
*/

static void			run_process_cycle(t_corewar *corewar, t_process *process)
{
	t_instruction	*inst;
	t_op			*op;
	void			(*func)(t_corewar*, t_process*, t_paraminfo*);
	t_paraminfo		paraminfo;

	inst = ((t_instruction*)&corewar->memory[get_physical_addr(process->pc)]);
	op = get_op(inst->opcode);
	if (op == NULL || !load_params(op, inst, &paraminfo))
	{
		process->pc++;
		process->next_cycle++;
		return ;
	}
	func = g_op_func_tab[(int)op->opcode];
	func(corewar, process, &paraminfo);
	if (!process->is_jump)
	{
		process->pc++;
		if (op->has_argcode)
			process->pc++;
		process->pc += get_params_size(&paraminfo);
	}
	else
		process->is_jump = false;
	process->next_cycle += op->cycles;
}

static void	run_cycle(t_corewar *corewar)
{
	t_list		**curr;
	t_process	*process;

	curr = &corewar->processes;
	while (*curr != NULL)
	{
		process = (t_process*)(*curr)->content;
		if (process->next_cycle <= corewar->curr_cycle)
			run_process_cycle(corewar, process);
		curr = &(*curr)->next;
	}
}

t_player	*corewar_run(t_corewar *corewar)
{
	while (corewar->process_count > 0)
	{
		if (corewar->dump_nbr_cycle >= 0
			&& corewar->curr_cycle >= corewar->dump_nbr_cycle)
		{
			dump(corewar);
			return (NULL);
		}
		run_cycle(corewar);
		corewar->curr_cycle++;
		if (corewar->curr_cycle >= corewar->next_check_cycle)
		{
			check_alive(corewar);
			corewar->next_check_cycle += corewar->cycle_to_die;
		}
	}
	return (corewar->last_live);
}
