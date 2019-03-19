/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juazouz <juazouz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 17:08:21 by juazouz           #+#    #+#             */
/*   Updated: 2019/03/19 17:18:41 by juazouz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		read_memory(t_corewar *cw, int addr, size_t size, void *res)
{
	int		i;

	i = 0;
	while (i < (int)size)
	{
		*((char*)res + i) = *((char*)&cw->memory[(addr + i) % MEM_SIZE]);
		i++;
	}
}

static void		write_memory(t_corewar *cw, int addr, size_t size, void *ptr)
{
	int		i;

	i = 0;
	while (i < (int)size)
	{
		*((char*)&cw->memory[(addr + i) % MEM_SIZE]) = *((char*)ptr + i);
		i++;
	}
}

void	generic_read(t_corewar *corewar, t_memaccess *memaccess)
{
	int			reg_id;

	memaccess->value = 0;
	memaccess->success = true;
	if (memaccess->arg_type == REG_CODE)
	{
		reg_id = memaccess->paramval.reg_id;
		if (is_valid_reg(reg_id))
		{
			memaccess->value = (int)memaccess->process->reg[reg_id - 1];
		}
		else
		{
			memaccess->success = false;
		}
	}
	else if (memaccess->arg_type == DIR_CODE)
	{
		memaccess->value = (int)memaccess->paramval.dir;
	}
	else if (memaccess->arg_type == IND_CODE)
	{
		read_memory(corewar, memaccess->paramval.ind, memaccess->memsize,
			&memaccess->value);
	}
}

void	generic_write(t_corewar *corewar, t_memaccess *memaccess)
{
	int			reg_id;

	memaccess->success = true;
	if (memaccess->arg_type == REG_CODE)
	{
		reg_id = memaccess->paramval.reg_id;
		if (is_valid_reg(reg_id))
		{
			memaccess->process->reg[reg_id - 1] = (t_reg)memaccess->value;
		}
		else
		{
			memaccess->success = false;
		}
	}
	else if (memaccess->arg_type == DIR_CODE)
	{
		memaccess->paramval.dir = memaccess->value;
	}
	else if (memaccess->arg_type == IND_CODE)
	{
		write_memory(corewar, memaccess->paramval.ind, memaccess->memsize,
			&memaccess->value);
	}
}
