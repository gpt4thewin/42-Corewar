/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_endline.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbakhti <mbakhti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 02:49:48 by mbakhti           #+#    #+#             */
/*   Updated: 2019/03/08 19:14:21 by mbakhti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

_Bool	is_endline(char *tok, char next, t_pos cursor)
{
	if (tok[0] == '\n')
		return (true);
	return (false);
	(void)next;
	(void)cursor;
}
