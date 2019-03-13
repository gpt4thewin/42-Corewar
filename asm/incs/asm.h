/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbakhti <mbakhti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:46:06 by mbakhti           #+#    #+#             */
/*   Updated: 2019/03/13 15:49:39 by mbakhti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "libft.h"
# include "op.h"
# include "commons.h"
# include "lexer.h"
# include "parser.h"
# include <fcntl.h>

typedef struct	s_env
{
	char		*assembly;
	t_token		*tokens;
	t_bytecode	bytecode;
}				t_env;

void			check_arguments(int argc, char *argv[]);
void			store_assembly(char **instructions, char *filename);
void			compile_champion(t_bytecode champion, char *filename);
void			ft_exit_error(char *message);

#endif
