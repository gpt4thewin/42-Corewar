/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_parameters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juazouz <juazouz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 14:40:40 by juazouz           #+#    #+#             */
/*   Updated: 2019/03/29 13:30:24 by juazouz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int		parse_number(int *pos, const char *av[])
{
	char	*str;
	int		i;
	int		res;

	(*pos)++;
	if (av[*pos] == NULL || av[*pos][0] == '\0')
		corewar_die(MSG_COMMAND_LINE_ERROR);
	str = (char*)av[*pos];
	res = 0;
	i = 0;
	while (str[i] != 0)
	{
		if (!ft_isdigit(str[i]))
			corewar_die(MSG_COMMAND_LINE_ERROR);
		res *= 10;
		res += str[i] - '0';
		i++;
	}
	return (res);
}

static void		parse_champion(t_corewar *corewar, int *pos, const char *av[])
{
	t_player	*player;

	player = &corewar->players[corewar->players_count];
	player->id = -1;
	if (ft_strequ("-n", av[*pos]))
	{
		player->id = parse_number(pos, av);
		(*pos)++;
	}
	if (av[*pos] == NULL)
		corewar_die(MSG_COMMAND_LINE_ERROR);
	if (corewar->players_count >= MAX_PLAYERS)
	{
		ft_fprintf(2, "Up to %d max players allowed\n", MAX_PLAYERS);
		exit(EXIT_FAILURE);
	}
	player->file = av[*pos];
	(*pos)++;
	corewar->players_count++;
}

static void		parse_option(t_arguments *arguments, int *pos, const char *av[])
{
	if (ft_strequ("-dump_cycle", av[*pos]))
	{
		arguments->dump_cycle = true;
		arguments->dump_nbr_cycle = parse_number(pos, av);
	}
	else if (ft_strequ("-dump", av[*pos]))
	{
		arguments->dump_cycle = false;
		arguments->dump_nbr_cycle = parse_number(pos, av);
	}
	else if (ft_strequ("-v", av[*pos]))
	{
		arguments->verbosity = parse_number(pos, av);
	}
	else if (ft_strequ("-c", av[*pos]))
	{
		arguments->dump_colors = true;
	}
	else if (ft_strequ("-h", av[*pos]))
	{
		arguments->usage = true;
	}
	else
	{
		ft_fprintf(2, "Unknown option : %s\n", av[*pos]);
		corewar_die("");
	}
	(*pos)++;
}

static void		players_init_color(t_corewar *corewar)
{
	int cpt;

	cpt = 0;
	while (cpt < corewar->players_count && cpt < MAX_PLAYERS)
	{
		corewar->players[cpt].color = (cpt + 1) % MAX_PLAYERS;
		cpt++;
	}
}

void			parse_parameters(t_corewar *corewar, int ac, const char *av[])
{
	int	i;

	if (ac == 1)
	{
		corewar_die("ERROR: no argument");
	}
	i = 1;
	while (av[i] != NULL && av[i][0] == '-')
	{
		parse_option(&corewar->arguments, &i, av);
	}
	while (i < ac)
	{
		parse_champion(corewar, &i, av);
	}
	if (corewar->players_count <= 0)
		corewar_die("ERROR: no champions specified");
	players_init_color(corewar);
	players_init_id(corewar);
}
