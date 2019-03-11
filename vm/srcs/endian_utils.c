/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endian_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juazouz <juazouz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 18:04:45 by juazouz           #+#    #+#             */
/*   Updated: 2019/03/11 19:05:20 by juazouz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	swap(char *a, char *b)
{
	char	tmp;

	tmp = *b;
	*b = *a;
	*a = tmp;
}

/*
**	Converts little endian to big endian (or the other way around).
*/

int		to_little_endian32(int val)
{
	int		res;
	char	*array;

	res = val;
	array = (char*)&res;
	swap(&array[0], &array[3]);
	swap(&array[1], &array[2]);
	return (res);
}
