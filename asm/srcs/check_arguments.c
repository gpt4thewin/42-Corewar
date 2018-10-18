/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbakhti <mbakhti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 20:39:06 by mbakhti           #+#    #+#             */
/*   Updated: 2019/03/09 03:12:54 by mbakhti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		display_usage(char *path_to_binary)
{
	ft_printf("usage: %s <sourcefile.s>\n", path_to_binary);
	exit(EXIT_FAILURE);
}

static _Bool	wrong_extension(char *sourcefile)
{
	if (!ft_strequ(".s", sourcefile + (ft_strlen(sourcefile) - 2)))
		return (true);
	return (false);
}

void			check_arguments(int argc, char *argv[])
{
	if (argc != 2 || wrong_extension(argv[1]))
		display_usage(argv[0]);
}
