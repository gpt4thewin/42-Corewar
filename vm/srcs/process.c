/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juazouz <juazouz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 15:12:12 by juazouz           #+#    #+#             */
/*   Updated: 2019/03/14 15:14:19 by juazouz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_process	*process_new(void)
{
	t_process	*res;

	res = ft_memalloc(sizeof(t_process));
	return (res);
}

t_process	*process_copy(t_process *process)
{
	t_process	*res;

	res = process_new();
	ft_memcpy(res, process, sizeof(t_process));
	return (res);
}
