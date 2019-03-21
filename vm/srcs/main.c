/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juazouz <juazouz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:46:41 by mbakhti           #+#    #+#             */
/*   Updated: 2019/03/21 19:08:52 by juazouz          ###   ########.fr       */
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
	winner = corewar_run(corewar);
	if (winner != NULL)
		printf("Le joueur %d(%s) a gagné.\n", winner->id, winner->prog_name);
	free(corewar);
	return (EXIT_SUCCESS);
}
