/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juazouz <juazouz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 17:08:21 by juazouz           #+#    #+#             */
/*   Updated: 2019/03/21 16:40:46 by juazouz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int				get_physical_addr(int addr)
{
	if (addr < 0)
	{
		addr += MEM_SIZE;
		addr += (-addr / MEM_SIZE) * MEM_SIZE;
	}
	return (addr % MEM_SIZE);
}

static int		get_virtual_addr(t_memaccess *memaccess)
{
	int		addr;

	addr = (memaccess->process->pc + memaccess->param.value.ind);
	if (memaccess->idxmod)
		addr %= IDX_MOD;
	return (addr);
}

static void		read_memory(t_corewar *cw, t_memaccess *memaccess)
{
	int		i;
	int		addr;
	char	tmp;

	addr = get_virtual_addr(memaccess);
	i = 0;
	while (i < (int)memaccess->value_size)
	{
		tmp = *((char*)&cw->memory[get_physical_addr(addr)]);
		*((char*)&memaccess->value + i) = tmp;
		addr++;
		i++;
	}
}

static void		write_memory(t_corewar *cw, t_memaccess *memaccess)
{
	int		i;
	int		addr;
	char	tmp;

	addr = get_virtual_addr(memaccess);
	i = 0;
	while (i < (int)memaccess->value_size)
	{
		tmp = *((char*)&memaccess->value + i);
		*((char*)&cw->memory[get_physical_addr(addr)]) = tmp;
		addr++;
		i++;
	}
}

void	generic_read(t_corewar *corewar, t_memaccess *memaccess)
{
	int			reg_id;

	memaccess->value = 0;
	if (memaccess->param.type == REG_CODE)
	{
		reg_id = memaccess->param.value.reg_id;
		memaccess->value = (int)memaccess->process->reg[reg_id - 1];
	}
	else if (memaccess->param.type == DIR_CODE)
	{
		memaccess->value = (int)memaccess->param.value.dir;
	}
	else if (memaccess->param.type == DIR_MOD_CODE)
	{
		memaccess->value = (int)memaccess->param.value.ind;
	}
	else if (memaccess->param.type == IND_CODE)
	{
		read_memory(corewar, memaccess);
	}
	else
	{
		ft_fprintf(2, "Error: invalid instruction\n");
	}
}

void	generic_write(t_corewar *corewar, t_memaccess *memaccess)
{
	int			reg_id;

	if (memaccess->param.type == REG_CODE)
	{
		reg_id = memaccess->param.value.reg_id;
		memaccess->process->reg[reg_id - 1] = (t_reg)memaccess->value;
	}
	else if (memaccess->param.type == IND_CODE)
	{
		write_memory(corewar, memaccess);
	}
	else
	{
		ft_fprintf(2, "Error: invalid instruction\n");
	}
}
