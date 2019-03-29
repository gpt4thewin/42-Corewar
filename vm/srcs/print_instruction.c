/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_instruction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juazouz <juazouz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 13:20:34 by juazouz           #+#    #+#             */
/*   Updated: 2019/03/29 13:38:03 by juazouz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	print_argument(t_param *param)
{
	if (param->type == REG_CODE)
		ft_printf(" r%d", param->value.reg_id);
	else if (param->type == IND_CODE || param->type == DIR_MOD_CODE)
		ft_printf(" %d", param->value.ind);
	else if (param->type == DIR_CODE)
		ft_printf(" %d", param->value.dir);
	else
		ft_printf(" ??");
}

void		print_instruction(t_process *process)
{
	int	i;

	ft_printf("P    %-2d| %s", process->id, process->op->opname);
	i = 0;
	while (i < process->paraminfo.args_number)
	{
		print_argument(&process->paraminfo.params[i]);
		i++;
	}
	ft_printf("\n");
}
