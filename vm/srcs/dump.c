/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoulas <agoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 17:44:00 by juazouz           #+#    #+#             */
/*   Updated: 2019/03/14 19:21:21 by agoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

// Taille de MEM_SIZE
void			dump(char *memory)
{
	int i;

	i = 0;
	ft_printf("0x%04x : ", 0);
	while(i < MEM_SIZE)
	{
		ft_printf("%02.2hhx", memory[i]);
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
