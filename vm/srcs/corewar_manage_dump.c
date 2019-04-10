/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_manage_dump.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juazouz <juazouz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 19:57:39 by juazouz           #+#    #+#             */
/*   Updated: 2019/04/10 20:00:19 by juazouz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	Manages the dumps option every cycle.
**	Returns true to force the termination of the VM.
*/

t_bool	corewar_manage_dump(t_corewar *corewar)
{
	char	tmp;

	if (corewar->arguments.dump_cycle)
	{
		if (corewar->curr_cycle % corewar->arguments.dump_nbr_cycle == 0)
		{
			dump(corewar);
			read(STDIN_FILENO, &tmp, 1);
			return (false);
		}
	}
	else if (corewar->arguments.dump_nbr_cycle >= 0
		&& corewar->arguments.dump_nbr_cycle <= corewar->curr_cycle)
	{
		dump(corewar);
		return (true);
	}
	return (false);
}
