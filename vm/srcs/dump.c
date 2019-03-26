/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoulas <agoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 17:44:00 by juazouz           #+#    #+#             */
/*   Updated: 2019/03/22 19:09:49 by agoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	print_hex_color(t_corewar *corewar, int pos)
{
	int i;

	i = corewar->map_memory_color[pos];
	if (i == RED)
	{
		ft_printf("\033[1;31m");
	}
	else if (i == GREEN)
	{
		ft_printf("\033[0;32m");
	}
	else if (i == YELLOW)
	{
		ft_printf("\033[1;33m");
	}
	else if (i == BLUE)
	{
		ft_printf("\033[1;34m");
	}
	ft_printf("%02.2hhx", corewar->memory[pos]);
	ft_printf("\033[0m");
}

/*
** Print the simulated memory.
*/

void		dump(t_corewar *corewar)
{
	int	i;

	i = 0;
	ft_printf("0x%04x : ", 0);
	while (i < MEM_SIZE)
	{
		print_hex_color(corewar, i);
		if (((i + 1) % MAX_SIZE_DUMP != 0))
			ft_printf(" ");
		else
		{
			ft_printf("\n");
			if (i < (MEM_SIZE - 1))
				ft_printf("0x%04x : ", i + 1);
		}
		i++;
	}
}
