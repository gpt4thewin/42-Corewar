/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoulas <agoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 17:44:00 by juazouz           #+#    #+#             */
/*   Updated: 2019/03/18 16:05:52 by agoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"



void	print_color(t_corewar *corewar, int pos)
{
	int i;

	i = corewar->id_memory[pos];
	if (i == 0)
	{
		 ft_printf("\033[1;31m");
	}
	else if (i == 1)
	{
		ft_printf("\033[0;32m");
	}
	else if (i == 2)
	{
		ft_printf("\033[1;31m");
	}
	else if (i == 3)
	{
		ft_printf("\033[1;33m");
	}
	ft_printf ("%02.2hhx", corewar->memory[pos]);
	ft_printf("\033[0m");



}
// Taille de MEM_SIZE
void			dump(t_corewar *corewar)
{
	int i;

	i = 0;
	ft_printf("0x%04x : ", 0);
	while(i < MEM_SIZE)
	{
		//ft_printf("%02.2hhx", corewar->memory[i]);
		print_color(corewar, i);
		if (((i + 1) % 64 != 0))
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
