/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoulas <agoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:46:41 by mbakhti           #+#    #+#             */
/*   Updated: 2019/03/28 14:53:16 by agoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	load_players(t_corewar *corewar)
{
	int	i;

	i = 0;
	while (i < corewar->players_count)
	{
		player_load(&corewar->players[i]);
		i++;
	}
}

int			main(int ac, const char *av[])
{
	t_corewar	*corewar;
	t_player	*winner;

	corewar = corewar_new();
	parse_parameters(corewar, ac, av);
	load_players(corewar);
	setup_players(corewar);
	print_start_fight(corewar);
	winner = corewar_run(corewar);
	if (winner != NULL)
		printf("Le joueur %d(%s) a gagné.\n", winner->id, winner->prog_name);
	free(corewar);
	return (EXIT_SUCCESS);
}
