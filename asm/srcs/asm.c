/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbakhti <mbakhti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:46:09 by mbakhti           #+#    #+#             */
/*   Updated: 2019/03/08 21:27:37 by mbakhti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_exit_error(char *message)
{
	ft_putendl_fd(message, 2);
	exit(EXIT_FAILURE);
}

int		main(int argc, char *argv[])
{
	t_env	champion;

	check_arguments(argc, argv);
	store_assembly(&champion.assembly, argv[1]);
	lex_assembly(&champion.tokens, champion.assembly);
	parse_tokens(&champion.bytecode, champion.tokens);
	compile_champion(champion.bytecode, argv[1]);
	return (EXIT_SUCCESS);
}
