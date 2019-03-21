/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoulas <agoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 16:24:47 by agoulas           #+#    #+#             */
/*   Updated: 2019/03/21 19:03:01 by agoulas          ###   ########.fr       */
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
