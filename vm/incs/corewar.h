/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juazouz <juazouz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:46:43 by mbakhti           #+#    #+#             */
/*   Updated: 2019/03/11 16:01:50 by juazouz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "libft.h"
# include "op.h"

typedef struct s_player		t_player;
typedef struct s_player		t_player;
typedef struct s_process	t_process;
typedef struct s_corewar	t_corewar;

/*
**	Corewar virtual machine.
*/

struct						s_player
{
	int			id;
	int			last_check;
	int			load_addr;
	char		program[CHAMP_MAX_SIZE];
};

struct						s_process
{
	t_player	*player;
	int			next_cycle;
	int			pc;
	int			reg[REG_NUMBER];
	t_bool		carry;
};

struct						s_corewar
{
	int			curr_cycle;
	int			players_count;
	t_player	players[MAX_PLAYERS];
	int			cycle_to_die;
	int			process_count;
	t_process	*processes;
	int			dump_nbr_cycle;
	char		memory[MEM_SIZE];
};

struct						s_instruction
{
	char		opcode;
	t_arg_type	arg_type_1:2;
	t_arg_type	arg_type_2:2;
	t_arg_type	arg_type_3:2;
	t_arg_type	arg_type_4:2;
	int			parameters[0];
};

#endif
