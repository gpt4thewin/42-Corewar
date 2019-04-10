/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoulas <agoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:46:41 by mbakhti           #+#    #+#             */
/*   Updated: 2019/04/10 19:49:23 by agoulas          ###   ########.fr       */
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

static void	print_usage(void)
{
	ft_printf("Usage:\t./corewar [-dump N] [-dump_cycle B] [-v A] [-c]"
		"-n A <champion1.cor> <...>\n");
	ft_printf("\t-dump: dumps the memory after N cycles and exits.\n");
	ft_printf("\t-dump_cycle: dumps the memory every N cycles.\n");
	ft_printf("\t-c: colorates the dumped memory.\n");
	ft_printf("\t-v: Verbosity levels.\n");
	ft_printf("\t\t%5s : %-20s\n", "1", "Prints death");
	ft_printf("\t\t%5s : %-20s\n", "2", "Prints live");
	ft_printf("\t\t%5s : %-20s\n", "4", "Prints instructions");
	ft_printf("\t\t%5s : %-20s\n", "8", "Prints aff output");
	ft_printf("\t\t%5s : %-20s\n", "16", "Prints CDT");
	ft_printf("\t\t%5s : %-20s\n", "32", "Prints process count");
	ft_printf("\t-n: attribute a id A to the player.\n");
}

int			main(int ac, const char *av[])
{
	t_corewar	*corewar;
	t_player	*winner;

	corewar = corewar_new();
	parse_parameters(corewar, ac, av);
	if (corewar->arguments.usage)
	{
		print_usage();
		return (EXIT_SUCCESS);
	}
	load_players(corewar);
	setup_players(corewar);
	print_start_fight(corewar);
	winner = corewar_run(corewar);
	if (winner != NULL)
		ft_printf("Le joueur %d(%s) a gagné.\n", winner->id,
			winner->prog_name);
	corewar_free(corewar);
	return (EXIT_SUCCESS);
}
