/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_players.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoulas <agoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 13:50:54 by juazouz           #+#    #+#             */
/*   Updated: 2019/03/21 19:11:26 by agoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	*ft_memcpy_color(t_corewar *corewar, t_player *player, size_t num,
	size_t pos)
{
	size_t	i;
	void	*dst;
	void	*src;

	dst = corewar->memory;
	src = &player->program;
	if (dst == src)
		return (dst);
	i = 0;
	while (i < num)
	{
		((unsigned char*)dst)[pos + i] = ((unsigned char*)src)[i];
		corewar->map_memory_color[pos + i] = player->color;
		i++;
	}
	return (dst);
}

void	setup_player_at_pos(t_corewar *corewar, t_player *player, size_t pos)
{
	t_process	*entry_process;

	ft_memcpy_color(corewar, player, CHAMP_MAX_SIZE, pos);
	corewar->map_memory_color[pos] = player->color;
	entry_process = process_new();
	entry_process->pc = pos;
	entry_process->player = player;
	process_set_reg(entry_process, 1, player->id);
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
