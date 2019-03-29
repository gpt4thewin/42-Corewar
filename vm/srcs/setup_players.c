/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_players.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juazouz <juazouz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 13:50:54 by juazouz           #+#    #+#             */
/*   Updated: 2019/03/29 15:09:28 by juazouz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	setup_player_at_pos(t_corewar *corewar, t_player *player, size_t pos)
{
	t_process	*entry_process;

	memcpy_color(corewar, player, player->prog_size, pos);
	corewar->map_memory_color[pos] = player->color;
	entry_process = process_new();
	entry_process->pc = pos;
	entry_process->player = player;
	process_set_reg(entry_process, 1, -player->id);
	corewar_add_process(corewar, entry_process);
}

/*
**	Setups the initial memory and processes of players in memory.
*/

void	setup_players(t_corewar *corewar)
{
	int			i;
	size_t		offset;
	size_t		pos;
	t_player	*player;

	offset = MEM_SIZE / corewar->players_count;
	pos = 0;
	i = 0;
	while (i < corewar->players_count)
	{
		player = &corewar->players[i];
		setup_player_at_pos(corewar, player, pos);
		pos += offset;
		i++;
	}
}
