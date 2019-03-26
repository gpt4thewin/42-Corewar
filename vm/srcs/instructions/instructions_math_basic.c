/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_math_basic.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoulas <agoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 18:25:54 by agoulas           #+#    #+#             */
/*   Updated: 2019/03/22 18:30:36 by agoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	inst_add_sub(t_process *process, t_paraminfo *param, int type)
{
	int			reg_id;
	int			val1;
	int			val2;
	int			res;

	reg_id = param->params[0].value.reg_id;
	val1 = process_get_reg(process, reg_id);
	reg_id = param->params[1].value.reg_id;
	val2 = process_get_reg(process, reg_id);
	if (type > 1 || add_profil < 0)
		corewar_die("instruction add_sub inconnu");
	res = (type == 1) ? (val1 + val2) : (val1 - val2);
	reg_id = param->params[2].value.reg_id;
	process_set_reg(process, reg_id, res);
	process->carry = (res == 0);
}

void		inst_add(t_corewar *corewar, t_process *process, t_paraminfo *param)
{
	(void)corewar;
	inst_add_sub(process, param, 1);
}

void		inst_sub(t_corewar *corewar, t_process *process, t_paraminfo *param)
{
	(void)corewar;
	inst_add_sub(process, param, 0);
}
