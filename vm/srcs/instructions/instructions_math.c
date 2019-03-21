/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions_math.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoulas <agoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 16:36:26 by juazouz           #+#    #+#             */
/*   Updated: 2019/03/21 18:23:47 by agoulas          ###   ########.fr       */
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
	ft_fprintf(2, "pc = %d, next_cycle :%d,nbr_live = %d \n",p->pc, p->next_cycle,p->nbr_live);
	while (i < REG_NUMBER)
	{
		ft_fprintf(2,"reg[%d] = %2.2hhx \n",i, p->reg[i]);
		if (i == (REG_NUMBER / 2))
			ft_fprintf(2,"\n");
		i++;
	}
	ft_fprintf(2,"\n___________________________________________________\n");
}

void	inst_add(t_corewar *corewar, t_process *process, t_paraminfo *param)
{
	t_memaccess	memaccess;
	int param1;
	int param2;

	debug_process(process);
	memaccess.idxmod = true;
	param1 = (int)process->reg[(int)param->params[0].value.reg_id - 1];
	param2 = (int)process->reg[(int)param->params[1].value.reg_id - 1];
	memaccess._value = param1 + param2;
	memaccess.process = process;
	memaccess.value_size = REG_SIZE;
	generic_write(corewar, &memaccess,param->params[2], memaccess._value);
	process->carry = (memaccess._value == 0);
	debug_process(process);
}

void	inst_sub(t_corewar *corewar, t_process *process, t_paraminfo *param)
{
	t_memaccess	memaccess;
	int param1;
	int param2;

	//debug_process(process);
	memaccess.idxmod = true;
	param1 = generic_read(corewar, &memaccess, param->params[0]);
	param2 = generic_read(corewar, &memaccess, param->params[1]);
	memaccess._value = param1 - param2;
	memaccess.process = process;
	memaccess.value_size = REG_SIZE;
	generic_write(corewar, &memaccess,param->params[2], memaccess._value);
	ft_printf("%02.2hhx - %02.2hhx = %02.2hhx\n",param1, param2, memaccess._value );
	process->carry = (memaccess._value == 0);
	//debug_process(process);
}

void	inst_and(t_corewar *corewar, t_process *process, t_paraminfo *param)
{
	t_memaccess	memaccess;
	int param1;
	int param2;

	debug_process(process);
	memaccess.idxmod = true;
	param1 = generic_read(corewar, &memaccess, param->params[0]);
	param2 = generic_read(corewar, &memaccess, param->params[1]);
	memaccess._value = (param1 & param2);
	memaccess.process = process;
	memaccess.value_size = REG_SIZE;

	generic_write(corewar, &memaccess,param->params[2], memaccess._value);
	process->carry = (memaccess._value == 0);
	debug_process(process);
}

void	inst_or(t_corewar *corewar, t_process *process, t_paraminfo *param)
{
	t_memaccess	memaccess;
	int param1;
	int param2;

debug_process(process);
	memaccess.idxmod = true;
	param1 = generic_read(corewar, &memaccess, param->params[0]);
	param2 = generic_read(corewar, &memaccess, param->params[1]);
	memaccess._value = (param1 | param2);
	memaccess.process = process;
	memaccess.value_size = REG_SIZE;
	generic_write(corewar, &memaccess,param->params[2], memaccess._value);
	process->carry = (memaccess._value == 0);
	 debug_process(process);
}

void	inst_xor(t_corewar *corewar, t_process *process, t_paraminfo *param)
{
	t_memaccess	memaccess;
	int param1;
	int param2;

	debug_process(process);
	memaccess.idxmod = true;
	param1 = generic_read(corewar, &memaccess, param->params[0]);
	param2 = generic_read(corewar, &memaccess, param->params[1]);
	memaccess._value = (param1 ^ param2);
	memaccess.process = process;
	memaccess.value_size = REG_SIZE;
	generic_write(corewar, &memaccess,param->params[2], memaccess._value);
	process->carry = (memaccess._value == 0);
	debug_process(process);
}
