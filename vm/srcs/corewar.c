/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoulas <agoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 16:58:10 by juazouz           #+#    #+#             */
/*   Updated: 2019/03/21 19:08:53 by agoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_corewar	*corewar_new(void)
{
	t_corewar	*res;
	int i;

	i = 0;
	res = ft_memalloc(sizeof(t_corewar));
	res->dump_nbr_cycle = -1;
	res->cycle_to_die = CYCLE_TO_DIE;
	while(i < MEM_SIZE)
	{
		res->map_memory_color[i] = WHITE;
		i++;
	}
	return (res);
}

void		corewar_die(char *msg)
{
	ft_fprintf(2, "%s\n", msg);
	exit(EXIT_FAILURE);
}
