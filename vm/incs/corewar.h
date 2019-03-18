/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoulas <agoulas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:46:43 by mbakhti           #+#    #+#             */
/*   Updated: 2019/03/18 14:42:55 by agoulas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "libft.h"
# include "op.h"
# include <stdio.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

/*
**	Defines.
*/

# define MSG_COMMAND_LINE_ERROR "Error: invalid command line."

typedef struct s_player			t_player;
typedef struct s_player			t_player;
typedef struct s_process		t_process;
typedef struct s_corewar		t_corewar;
typedef struct s_instruction	t_instruction;
typedef union u_paramval		t_paramval;
typedef struct s_arg_types_byte	t_arg_types_byte;
typedef enum e_color			t_color;

# if (REG_SIZE == 1)
typedef char					t_reg;
# elif (REG_SIZE == 2)
typedef short					t_reg;
# elif (REG_SIZE == 4)
typedef int						t_reg;
# elif (REG_SIZE == 8)
typedef long					t_reg;
# else
# error "Invalid REG_SIZE value."
# endif

# if (IND_SIZE == 1)
typedef char					t_ind;
# elif (IND_SIZE == 2)
typedef short					t_ind;
# elif (IND_SIZE == 4)
typedef int						t_ind;
# elif (IND_SIZE == 8)
typedef long					t_ind;
# else
# error "Invalid IND_SIZE value."
# endif

# if (DIR_SIZE == 1)
typedef char					t_dir;
# elif (DIR_SIZE == 2)
typedef short					t_dir;
# elif (DIR_SIZE == 4)
typedef int						t_dir;
# elif (DIR_SIZE == 8)
typedef long					t_dir;
# else
# error "Invalid DIR_SIZE value."
# endif

/*
**	Union of all parameters types of varying size.
*/

union							u_paramval
{
	t_reg		reg;
	t_ind		ind;
	t_dir		dir;
};

/*
**	Player.
*/

struct						s_player
{
	int			id;
	int			last_check;
	const char	*file;
	char		prog_name[PROG_NAME_LENGTH + 1];
	char		program[CHAMP_MAX_SIZE];
};

/*
**	Color for print.
*/

enum 						s_color
{

	GREEN,
	BLUE,
	RED,
	YELLOW,
	WHITE
};

/*
**	Virtual machine task / thread / process.
*/

struct						s_process
{
	t_player	*player;
	int			next_cycle;
	int			pc;
	t_reg		reg[REG_NUMBER];
	t_bool		carry;
	int			nbr_live;
};

/*
**	Corewar virtual machine.
*/

struct						s_corewar
{
	int			curr_cycle;
	int			next_check_cycle;
	int			players_count;
	t_player	players[MAX_PLAYERS];
	t_player	*last_live;
	int			cycle_to_die;
	int			total_nbr_live;
	int			process_count;
	t_list		*processes;
	int			dump_nbr_cycle;
	int			id_memory[MEM_SIZE];
	char		memory[MEM_SIZE];
};

/*
**	Byte code instruction with parameters.
*/

struct	s_arg_types_byte
{
	t_arg_type	arg_type_1:2;
	t_arg_type	arg_type_2:2;
	t_arg_type	arg_type_3:2;
	t_arg_type	arg_type_4:2;
};

# define MAX_ARGS_TYPE_BYTES \
	(MAX_ARGS_NUMBER / 4 + (MAX_ARGS_NUMBER % 4 > 0 ? 1 : 0))

struct						s_param
{
	t_arg_types_byte	arg_types[MAX_ARGS_TYPE_BYTES];
	char				parameters[0];
};

union						u_param
{
	t_reg			single_reg;
	struct s_param	multi;
};

struct						s_instruction
{
	char			opcode;
	union u_param	param;
};

/*
**	Corewar.
*/

t_corewar		*corewar_new(void);
t_player		*corewar_run(t_corewar *corewar);
void			corewar_die(char *msg);

/*
**	Memory dump command line option.
*/

void			dump(t_corewar *corewar);

/*
**	Player setup.
*/

void			setup_players(t_corewar *corewar);

/*
**	Command line parser.
*/

void			parse_parameters(t_corewar *corewar, int ac, const char *av[]);

/*
**	Player.
*/

void			player_load(t_player *player);

/*
**	Process.
*/

t_process	*process_new(void);
t_process	*process_copy(t_process *process);

/*
**	Utils.
*/

int				to_little_endian32(int val);

/*
**	Instruction utils.
*/

t_bool	is_valid_reg(int reg_id);
t_reg	get_reg_value(t_process *process, int reg_id);

/*
**	Instructions processing.
*/

extern	int	(*g_op_func_tab[])(t_corewar*, t_process*, t_instruction*);

int		inst_live(t_corewar *corewar, t_process *process, t_instruction*);
int		inst_ld(t_corewar *corewar, t_process *process, t_instruction*);
int		inst_st(t_corewar *corewar, t_process *process, t_instruction*);
int		inst_add(t_corewar *corewar, t_process *process, t_instruction*);
int		inst_sub(t_corewar *corewar, t_process *process, t_instruction*);
int		inst_and(t_corewar *corewar, t_process *process, t_instruction*);
int		inst_or(t_corewar *corewar, t_process *process, t_instruction*);
int		inst_xor(t_corewar *corewar, t_process *process, t_instruction*);
int		inst_zjmp(t_corewar *corewar, t_process *process, t_instruction*);
int		inst_ldi(t_corewar *corewar, t_process *process, t_instruction*);
int		inst_sti(t_corewar *corewar, t_process *process, t_instruction*);
int		inst_fork(t_corewar *corewar, t_process *process, t_instruction*);
int		inst_lld(t_corewar *corewar, t_process *process, t_instruction*);
int		inst_lldi(t_corewar *corewar, t_process *process, t_instruction*);
int		inst_lfork(t_corewar *corewar, t_process *process, t_instruction*);
int		inst_aff(t_corewar *corewar, t_process *process, t_instruction*);

#endif
