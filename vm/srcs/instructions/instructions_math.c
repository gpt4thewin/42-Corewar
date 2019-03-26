/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions_math.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juazouz <juazouz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 16:36:26 by juazouz           #+#    #+#             */
/*   Updated: 2019/03/26 16:00:04 by juazouz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void debug_player(t_player player)
{
	ft_fprintf(2, "id = %d,name :%s \n",player.id, player.prog_name);
	ft_fprintf(2,"color = %d, file = %s\n", player.color, player.file);
	ft_fprintf(2,"last_check = %d\n", player.last_check);
}


void debug_process(t_process *p)
{
	int i;

	i = 0;
	ft_fprintf(2,"\n___________________________________________________\n");
	debug_player(*p->player);
	ft_fprintf(2, "pc = %d, exec_cycle :%d,nbr_live = %d \n",p->pc, p->exec_cycle, p->nbr_live);
	while (i < REG_NUMBER)
	{
		ft_fprintf(2,"reg[%d] = %d \n",i, p->reg[i]);
		if (i == ((REG_NUMBER -1)/ 2))
			ft_fprintf(2,"\n");
		i++;
	}
	ft_fprintf(2,"\n___________________________________________________\n");
}

void	inst_add(t_corewar *corewar, t_process *process, t_paraminfo *param)
{
	int			reg_id;
	int			val1;
	int			val2;
	int 		res;

	(void)corewar;
	reg_id = param->params[0].value.reg_id;
	val1 = process_get_reg(process, reg_id);
	reg_id = param->params[1].value.reg_id;
	val2 = process_get_reg(process, reg_id);
	debug_process(process);
	res = val1 + val2;
	reg_id = param->params[2].value.reg_id;
	process_set_reg(process, reg_id, res);
	process->carry = (res == 0);
	debug_process(process);
}

void	inst_sub(t_corewar *corewar, t_process *process, t_paraminfo *param)
{
	int			reg_id;
	int			val1;
	int			val2;
	int 		res;

	debug_process(process);
	reg_id = param->params[0].value.reg_id;
	val1 = process_get_reg(process, reg_id);
	reg_id = param->params[1].value.reg_id;
	val2 = process_get_reg(process, reg_id);
	res = val1 - val2;
	reg_id = param->params[2].value.reg_id;
	process_set_reg(process, reg_id, res);
	(void)corewar;
	process->carry = (res == 0);
	debug_process(process);
}

void	inst_and(t_corewar *corewar, t_process *process, t_paraminfo *param)
{
	t_memaccess	memaccess;
	t_param		sum_param;
	int			reg_id;

	debug_process(process);
	memaccess.idxmod = true;
	memaccess.process = process;
	memaccess.value_size = DIR_SIZE;
	sum_param.value.ind = generic_read(corewar, &memaccess, param->params[0]);
	sum_param.value.ind &= generic_read(corewar, &memaccess, param->params[1]);
	sum_param.type = IND_CODE;
	ft_fprintf(2," res = %d \n" , (generic_read(corewar, &memaccess, param->params[0]) & generic_read(corewar, &memaccess, param->params[1])));
	ft_fprintf(2," res  &= %d \n", sum_param.value.ind);
	reg_id = param->params[2].value.reg_id;
	process_set_reg(process, reg_id,  sum_param.value.ind);
	process->carry = (sum_param.value.ind == 0);
	debug_process(process);
}

void	inst_or(t_corewar *corewar, t_process *process, t_paraminfo *param)
{
	t_memaccess	memaccess;
	t_param		sum_param;
	int			reg_id;

	debug_process(process);
	memaccess.idxmod = true;
	memaccess.process = process;
	memaccess.value_size = DIR_SIZE;
	sum_param.value.ind = generic_read(corewar, &memaccess, param->params[0]);
	sum_param.value.ind |= generic_read(corewar, &memaccess, param->params[1]);
	sum_param.type = IND_CODE;
	reg_id = param->params[2].value.reg_id;
	process_set_reg(process, reg_id,  sum_param.value.ind);
	process->carry = (sum_param.value.ind == 0);
	debug_process(process);

}

void	inst_xor(t_corewar *corewar, t_process *process, t_paraminfo *param)
{
	t_memaccess	memaccess;
	t_param		sum_param;
	int			reg_id;

	debug_process(process);
	memaccess.idxmod = true;
	memaccess.process = process;
	memaccess.value_size = DIR_SIZE;
	sum_param.value.ind = generic_read(corewar, &memaccess, param->params[0]);
	sum_param.value.ind ^= generic_read(corewar, &memaccess, param->params[1]);
	sum_param.type = IND_CODE;
	ft_fprintf(2," res = %d \n" , (generic_read(corewar, &memaccess, param->params[0]) ^ generic_read(corewar, &memaccess, param->params[1])));
	ft_fprintf(2," res  ^= %d \n", sum_param.value.ind);
	reg_id = param->params[2].value.reg_id;
	process_set_reg(process, reg_id,  sum_param.value.ind);
	process->carry = (sum_param.value.ind == 0);
	debug_process(process);
}
