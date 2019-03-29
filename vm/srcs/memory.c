/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juazouz <juazouz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 17:08:21 by juazouz           #+#    #+#             */
/*   Updated: 2019/03/29 14:41:43 by juazouz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int		get_virtual_addr(t_memaccess *memaccess)
{
	int		addr;
	int		offset;

	offset = memaccess->m_param.value.ind;
	if (memaccess->idxmod)
		offset %= IDX_MOD;
	addr = (memaccess->process->pc + offset);
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
		*((char*)&memaccess->m_value + i) = tmp;
		addr++;
		i++;
	}
}

static void		write_memory(t_corewar *cw, t_memaccess *memaccess)
{
	int		i;
	int		addr;
	char	tmp;
	int		color;

	color = memaccess->process->player->color;
	addr = get_virtual_addr(memaccess);
	i = 0;
	while (i < (int)memaccess->value_size)
	{
		tmp = *((char*)&memaccess->m_value + i);
		*((char*)&cw->memory[get_physical_addr(addr)]) = tmp;
		cw->map_memory_color[get_physical_addr(addr)] = color;
		addr++;
		i++;
	}
}

int				generic_read(t_corewar *corewar, t_memaccess *memaccess,
	t_param param)
{
	int	reg_id;
	int	res;

	res = 0;
	memaccess->m_param = param;
	if (param.type == REG_CODE)
	{
		reg_id = param.value.reg_id;
		res = process_get_reg(memaccess->process, reg_id);
	}
	else if (param.type == IND_CODE)
	{
		read_memory(corewar, memaccess);
		res = convert_endian32(memaccess->m_value);
	}
	else if (param.type == DIR_CODE)
		res = (int)param.value.dir;
	else if (param.type == DIR_MOD_CODE)
		res = (int)param.value.ind;
	else
		ft_fprintf(2, "Error: invalid instruction\n");
	return (res);
}

void			generic_write(t_corewar *corewar, t_memaccess *memaccess,
	t_param param, int val)
{
	int			reg_id;

	memaccess->m_param = param;
	if (param.type == REG_CODE)
	{
		reg_id = param.value.reg_id;
		process_set_reg(memaccess->process, reg_id, val);
	}
	else if (param.type == IND_CODE)
	{
		memaccess->m_value = convert_endian32(val);
		write_memory(corewar, memaccess);
	}
	else
	{
		ft_fprintf(2, "Error: invalid instruction\n");
	}
}
