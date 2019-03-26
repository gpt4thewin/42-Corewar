/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_parameters_id.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoulas <agoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 18:43:40 by agoulas           #+#    #+#             */
/*   Updated: 2019/03/22 19:20:52 by agoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	REturn if a id is already used.
*/

static int		id_has_duplicate(t_corewar *corewar, int id)
{
	int cpt;
	int nb;

	nb = 0;
	cpt = corewar->players_count - 1;
	while (cpt >= 0)
	{
		if (corewar->players[cpt].id == id)
			nb++;
		cpt--;
	}
	return (nb);
}

static void		player_has_id(t_corewar *corewar, int cpt)
{
	int	i;

	i = 0;
	while (corewar->players[cpt].id == -1 && i < corewar->players_count)
	{
		if (corewar->players[cpt].id == -1
			&& !id_has_duplicate(corewar, i))
			corewar->players[cpt].id = i;
		i++;
	}
	if (id_has_duplicate(corewar, corewar->players[cpt].id) > 1)
		corewar_die("Error player : duplicate id");
}

/*
**	Test every player and give a id to player without id.
*/

void			players_init_id(t_corewar *corewar)
{
	int cpt;

	cpt = 0;
	while (cpt < corewar->players_count)
	{
		player_has_id(corewar, cpt);
		cpt++;
	}
}
