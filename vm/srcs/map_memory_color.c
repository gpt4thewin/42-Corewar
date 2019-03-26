/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_memory_color.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoulas <agoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 13:28:23 by agoulas           #+#    #+#             */
/*   Updated: 2019/03/25 13:35:00 by agoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	*memcpy_color(t_corewar *corewar, t_player *player, size_t num,
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
