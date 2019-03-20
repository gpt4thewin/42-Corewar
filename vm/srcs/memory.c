/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juazouz <juazouz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 17:08:21 by juazouz           #+#    #+#             */
/*   Updated: 2019/03/20 17:13:58 by juazouz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int		get_address(t_memaccess *memaccess)
{
	int		addr;

	addr = (memaccess->process->pc);
	if (memaccess->idxmod)
		addr %= IDX_MOD;
	return (addr);
}

static void		read_memory(t_corewar *cw, t_memaccess *memaccess)
{
	int		i;
	int		addr;
	char	tmp;

	addr = get_address(memaccess);
	i = 0;
	while (i < (int)memaccess->value_size)
	{
		tmp = *((char*)&cw->memory[addr % MEM_SIZE]);
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

	addr = get_address(memaccess);
	i = 0;
	while (i < (int)memaccess->value_size)
	{
		tmp = *((char*)&memaccess->value + i);
		*((char*)&cw->memory[addr % MEM_SIZE]) = tmp;
		addr++;
		i++;
	}
}

void	generic_read(t_corewar *corewar, t_memaccess *memaccess)
{
	int			reg_id;

	memaccess->value = 0;
	if (memaccess->param_type == REG_CODE)
	{
		reg_id = memaccess->param_val.reg_id;
		memaccess->value = (int)memaccess->process->reg[reg_id - 1];
	}
	else if (memaccess->param_type == DIR_CODE)
	{
		memaccess->value = (int)memaccess->param_val.dir;
	}
	else if (memaccess->param_type == IND_CODE)
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

	if (memaccess->param_type == REG_CODE)
	{
		reg_id = memaccess->param_val.reg_id;
		memaccess->process->reg[reg_id - 1] = (t_reg)memaccess->value;
	}
	else if (memaccess->param_type == IND_CODE)
	{
		write_memory(corewar, memaccess);
	}
	else
	{
		ft_fprintf(2, "Error: invalid instruction\n");
	}
}
