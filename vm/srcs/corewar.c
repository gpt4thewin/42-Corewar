/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juazouz <juazouz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 16:58:10 by juazouz           #+#    #+#             */
/*   Updated: 2019/03/29 15:53:02 by juazouz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_corewar	*corewar_new(void)
{
	t_corewar	*res;
	int			i;

	i = 0;
	res = ft_memalloc(sizeof(t_corewar));
	res->arguments.dump_nbr_cycle = -1;
	res->cycle_to_die = CYCLE_TO_DIE;
	res->next_check_cycle = CYCLE_TO_DIE;
	while (i < MEM_SIZE)
	{
		res->map_memory_color[i] = WHITE;
		i++;
	}
	return (res);
}

void		corewar_die(char *msg)
{
	ft_fprintf(2, "%s\n", msg);
	exit(EXIT_FAILURE);
}

void		corewar_add_process(t_corewar *corewar, t_process *process)
{
	ft_lstadd(&corewar->processes, ft_lstnew(process, sizeof(t_process)));
	corewar->process_count++;
}

void	corewar_free(t_corewar *corewar)
{
	t_list		*curr;
	t_process	*process;

	curr = corewar->processes;
	while (curr != NULL)
	{
		process = (t_process*)curr->content;
		ft_lstdelone(&curr, NULL);
	}
	free(corewar);
}
