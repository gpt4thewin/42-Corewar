/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_players.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoulas <agoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 13:50:54 by juazouz           #+#    #+#             */
/*   Updated: 2019/03/19 15:08:15 by agoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	*ft_memcpy_color(t_corewar *corewar, const void *src, size_t num, int color)
{
	size_t i;
	void *dst;

	dst = corewar->memory;
	if (dst == src)
		return (dst);
	i = 0;
	while (i < num)
	{
		((unsigned char*)dst)[i] = ((unsigned char*)src)[i];
		corewar->id_memory[i] = color;
		i++;
	}
	return (dst);
}

void	setup_player_at_pos(t_corewar *corewar, t_player *player, size_t pos)
{
	t_process	*entry_process;

	ft_memcpy_color(corewar, &player->program, CHAMP_MAX_SIZE, player->id);
	corewar->id_memory[pos] = player->id;
	entry_process = process_new();
	entry_process->pc = pos;
	entry_process->player = player;
	corewar->id_memory[pos] = player->id;
	ft_lstadd(&corewar->processes, ft_lstnew(entry_process, sizeof(t_process)));
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
