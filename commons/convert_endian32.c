/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_endian32.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbakhti <mbakhti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 14:51:32 by mbakhti           #+#    #+#             */
/*   Updated: 2019/03/13 15:51:49 by mbakhti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
