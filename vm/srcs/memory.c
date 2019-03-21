/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juazouz <juazouz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 17:08:21 by juazouz           #+#    #+#             */
/*   Updated: 2019/03/21 17:48:57 by juazouz          ###   ########.fr       */
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

	addr = (memaccess->process->pc + memaccess->_param.value.ind);
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
		*((char*)&memaccess->_value + i) = tmp;
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
		tmp = *((char*)&memaccess->_value + i);
		*((char*)&cw->memory[get_physical_addr(addr)]) = tmp;
		addr++;
		i++;
	}
}

int		generic_read(t_corewar *corewar, t_memaccess *memaccess,
	t_param param)
{
	int	reg_id;
	int	res;

	res = 0;
	memaccess->_param = param;
	if (param.type == REG_CODE)
	{
		reg_id = param.value.reg_id;
		res = (int)memaccess->process->reg[reg_id - 1];
	}
	else if (param.type == DIR_CODE)
	{
		res = (int)param.value.dir;
	}
	else if (param.type == DIR_MOD_CODE)
	{
		res = (int)param.value.ind;
	}
	else if (param.type == IND_CODE)
	{
		read_memory(corewar, memaccess);
		res = memaccess->_value;
	}
	else
	{
		ft_fprintf(2, "Error: invalid instruction\n");
	}
	return (res);
}

void	generic_write(t_corewar *corewar, t_memaccess *memaccess, t_param param,
	int val)
{
	int			reg_id;

	memaccess->_param = param;
	if (param.type == REG_CODE)
	{
		reg_id = param.value.reg_id;
		memaccess->process->reg[reg_id - 1] = (t_reg)val;
	}
	else if (param.type == IND_CODE)
	{
		memaccess->_value = val;
		write_memory(corewar, memaccess);
	}
	else
	{
		ft_fprintf(2, "Error: invalid instruction\n");
	}
}
