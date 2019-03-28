/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juazouz <juazouz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 13:35:04 by agoulas           #+#    #+#             */
/*   Updated: 2019/03/28 15:53:54 by juazouz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	print_player(t_corewar *corewar, int pos)
{
	t_player player;

	player = corewar->players[pos];
	ft_printf("* Player %d,", player.id);
	ft_printf(" weighing %d bytes,", player.prog_size);
	ft_printf(" \"%s\",", player.prog_name);
	ft_printf(" (\"%s\").", player.comment);
	ft_printf("\n");
}

void		print_start_fight(t_corewar *corewar)
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
