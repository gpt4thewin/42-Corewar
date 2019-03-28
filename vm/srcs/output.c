/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoulas <agoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 13:35:04 by agoulas           #+#    #+#             */
/*   Updated: 2019/03/28 15:21:11 by agoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"


static void print_player(t_corewar *corewar, int pos)
{
	t_player player;

	player = corewar->players[pos];
	ft_printf("* Player %d,",player.id);
	ft_printf(" weighing %d bytes,", player.header_prog_size);
	ft_printf(" \"%s\",", player.prog_name);
	ft_printf(" (\"%s\").", player.comment);
	ft_printf("\n");
}

void print_start_fight(t_corewar *corewar)
{
	int index;

	index = 0;
	ft_printf("Introducing contestants...\n");
	while (index < corewar->players_count)
	{
		print_player(corewar, index);
		index++;
	}
}
