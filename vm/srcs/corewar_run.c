/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_run.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoulas <agoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 19:23:09 by juazouz           #+#    #+#             */
/*   Updated: 2019/03/19 15:08:55 by agoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static t_op	*get_op(int opcode)
{
	t_op	*res;

	if (opcode >= OP_TAB_SIZE || opcode < 1)
		return (NULL);
	res = &g_op_tab[opcode - 1];
	return (res);
}

// t_paramval	load_arg_value(t_op *op, t_instruction *pc, int index, size_t *pos)
// {
// 	int					offset;
// 	t_arg_types_byte	*arg_types;
// 	t_arg_type			arg_type;
// 	t_paramval			res;

// 	arg_types = pc->param.multi.arg_types;
// 	offset = (index % 4) * 2;
// 	arg_type = (arg_types[index / 4].arg_type_1 >> offset) & (0xff << offset);
// 	if (arg_type == T_REG)
// 	{
// 		res.reg = *((t_reg*)&pc->param.multi.parameters[*pos]);
// 		(*pos) += sizeof(t_reg);
// 	}
// 	else if (arg_type == T_DIR || arg_type == T_LAB)
// 	{
// 		res.dir = *((t_dir*)&pc->param.multi.parameters[*pos]);
// 		(*pos) += sizeof(t_dir);
// 	}
// 	else if (arg_type == T_IND)
// 	{
// 		res.ind = *((t_dir*)&pc->param.multi.parameters[*pos]);
// 		(*pos) += sizeof(t_ind);
// 	}
// 	return (res);
// }

// t_bool		load_args(t_op *op, t_instruction *pc, t_paramval *args)
// {
// 	int		i;
// 	size_t	pos;

// 	ft_bzero(args, sizeof(t_paramval) * MAX_ARGS_NUMBER);
// 	if (!op->has_argcode)
// 	{
// 		args[0].reg = pc->param.single_reg;
// 		return (true);
// 	}
// 	i = 0;
// 	pos = 0;
// 	while (i < op->args_number)
// 	{
// 		args[i] = load_arg_value(op, pc, i, &pos);
// 		pc->param.multi.parameters[pos];
// 		i++;
// 	}
// }

/*
**	Runs the next instruction of the specified process.
*/

static void	run_process_cycle(t_corewar *corewar, t_process *process)
{
	t_instruction	*inst;
	t_op			*op;
	int				(*func)(t_corewar*, t_process*, t_instruction*);
	// t_paramval		args[MAX_ARGS_NUMBER];

	inst = ((t_instruction*)&corewar->memory[process->pc]);
	op = get_op(inst->opcode);
	if (op == NULL)
	{
		process->pc++;
		process->next_cycle++;
		return ;
	}
	// TODO verify arguments type.
	func = g_op_func_tab[(int)op->opcode];
	process->pc += func(corewar, process, inst);
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
		if (corewar->curr_cycle >= corewar->dump_nbr_cycle)
		{
			dump(corewar);
			return (NULL);
		}
		run_cycle(corewar);
		corewar->curr_cycle++;
	}
	return (winner);
}
