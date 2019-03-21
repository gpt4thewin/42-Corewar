/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_run.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juazouz <juazouz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 19:23:09 by juazouz           #+#    #+#             */
/*   Updated: 2019/03/21 13:28:44 by juazouz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int			get_params_size(t_paraminfo *paraminfo, t_bool size_mod)
{
	int	i;
	int	res;

	res = 0;
	i = 0;
	while (i < paraminfo->args_number)
	{
		res += sizeof_param_type(paraminfo->params[i].type, size_mod);
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

/*
**	Runs the next instruction of the specified process.
*/

static void			run_process_cycle(t_corewar *corewar, t_process *process)
{
	t_instruction	*inst;
	t_op			*op;
	void			(*func)(t_corewar*, t_process*, t_paraminfo*);
	t_paraminfo		paraminfo;

	inst = ((t_instruction*)&corewar->memory[process->pc]);
	op = get_op(inst->opcode);
	if (op == NULL
		|| !load_params(op, inst, &paraminfo))
	{
		// TODO: Verifier le saut des instructions pour les mauvais types de parametres.
		process->pc++;
		process->next_cycle++;
		return ;
	}
	// TODO verify arguments type.
	func = g_op_func_tab[(int)op->opcode];
	func(corewar, process, &paraminfo);
	process->pc++;
	if (op->has_argcode)
		process->pc++;
	process->pc += get_params_size(&paraminfo, op->has_size_mod);
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
	t_player	*winner;

	winner = NULL;
	while (winner == NULL)
	{
		if (corewar->dump_nbr_cycle >= 0
			&& corewar->curr_cycle >= corewar->dump_nbr_cycle)
		{
			dump(corewar);
			return (NULL);
		}
		run_cycle(corewar);
		corewar->curr_cycle++;
	}
	return (winner);
}
