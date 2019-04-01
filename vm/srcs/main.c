/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juazouz <juazouz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:46:41 by mbakhti           #+#    #+#             */
/*   Updated: 2019/03/29 17:50:59 by juazouz          ###   ########.fr       */
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
	if (corewar->arguments.usage)
	{
		ft_printf("Usage:\t./corewar [-dump N] [-dump_cycle B] [-v N] [-c]"
			" <champion1.cor> <...>\n");
		ft_printf("\t-dump: dumps the memory after N cycles and exits.\n");
		ft_printf("\t-dump_cycle: dumps the memory every N cycles.\n");
		ft_printf("\t-c: colorates the dumped memory.\n");
		ft_printf("\t-v: Verbosity levels.\n");
		return (EXIT_SUCCESS);
	}
	load_players(corewar);
	setup_players(corewar);
	print_start_fight(corewar);
	winner = corewar_run(corewar);
	if (winner != NULL)
		ft_printf("Le joueur %d(%s) a gagné.\n", winner->id, winner->prog_name);
	corewar_free(corewar);
	return (EXIT_SUCCESS);
}
