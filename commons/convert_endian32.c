/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_endian32.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juazouz <juazouz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 14:51:32 by mbakhti           #+#    #+#             */
/*   Updated: 2019/03/21 15:46:59 by juazouz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commons.h"

static void	swap(char *a, char *b)
{
	char	tmp;

	tmp = *b;
	*b = *a;
	*a = tmp;
}

int			convert_endian32(int val)
{
	int		num;
	int		res;
	char	*array;

	num = 1;
	if (*(char *)&num == 1)
	{
		res = val;
		array = (char *)&res;
		swap(&array[0], &array[3]);
		swap(&array[1], &array[2]);
		return (res);
	}
	return (val);
}

int			convert_endian16(short val)
{
	int		num;
	short	res;
	char	*array;

	num = 1;
	if (*(char *)&num == 1)
	{
		res = val;
		array = (char *)&res;
		swap(&array[0], &array[1]);
		return (res);
	}
	return (val);
}

void		convert_endian_size(void *ptr, int size)
{
	int			i;
	int			num;

	num = 1;
	if (!(*(char *)&num == 1))
		return ;
	i = 0;
	while (i < size / 2)
	{
		swap((char*)(ptr + i), (char*)(ptr - i - 1));
		i++;
	}
}
