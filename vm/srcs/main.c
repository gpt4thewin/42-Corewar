/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juazouz <juazouz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:46:41 by mbakhti           #+#    #+#             */
/*   Updated: 2019/03/11 17:04:01 by juazouz          ###   ########.fr       */
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

	corewar = corewar_new();
	parse_parameters(corewar, ac, av);
	load_players(corewar);
	free(corewar);
	return (EXIT_SUCCESS);
}
