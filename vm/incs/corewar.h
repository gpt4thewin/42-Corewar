/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juazouz <juazouz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:46:43 by mbakhti           #+#    #+#             */
/*   Updated: 2019/03/20 17:03:39 by juazouz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "libft.h"
# include "op.h"
# include "commons.h"
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
typedef struct s_memaccess		t_memaccess;
typedef enum e_color			t_color;
typedef struct s_paraminfo		t_paraminfo;

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
	char		reg_id;
	t_ind		ind;
	t_dir		dir;
};

struct							s_paraminfo
{
	char			args_number;
	t_arg_type		types[MAX_ARGS_NUMBER];
	t_paramval		values[MAX_ARGS_NUMBER];
};

/*
**	Enum of color for print dump.
*/

enum 							e_color
{
	BLUE,
	GREEN,
	RED,
	YELLOW,
	WHITE
};

/*
**	Player.
*/

struct						s_player
{
	int			id;
	t_color		color;
	int			last_check;
	const char	*file;
	char		prog_name[PROG_NAME_LENGTH + 1];
	char		program[CHAMP_MAX_SIZE];
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
	t_color		id_memory[MEM_SIZE];
	char		memory[MEM_SIZE];
};

/*
**	Generic memory read/write information.
**	Contains both parameters and result.
*/

struct						s_memaccess
{
	t_process	*process;
	t_arg_type	arg_type;
	t_paramval	paramval;
	t_bool		idxmod;
	size_t		value_size;
	int			value;
	t_bool		success;
};

/*
**	Byte code instruction with parameters.
*/

# define MAX_ARGS_TYPE_BYTES \
	(MAX_ARGS_NUMBER / 4 + (MAX_ARGS_NUMBER % 4 > 0 ? 1 : 0))

struct						s_param
{
	unsigned char	arg_type_4:2;
	unsigned char	arg_type_3:2;
	unsigned char	arg_type_2:2;
	unsigned char	arg_type_1:2;
	char			parameters[0];
};

union						u_param
{
	t_dir			single_dir;
	struct s_param	multi;
	char			debug8;
	char			debug16;
};

struct						s_instruction
{
	char			opcode;
	union u_param	param;
}__attribute__((packed, aligned(1)));

/*
**	Corewar.
*/

t_corewar		*corewar_new(void);
t_player		*corewar_run(t_corewar *corewar);
void			corewar_die(char *msg);
t_reg			corewar_reg_read(t_corewar *corewar, int pc, int addr);
void			corewar_reg_write(t_corewar *corewar, int pc, int addr, t_reg val);

/*
**	Memory.
*/

void			generic_read(t_corewar *corewar, t_memaccess *memaccess);
void			generic_write(t_corewar *corewar, t_memaccess *memaccess);

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

t_process		*process_new(void);
t_process		*process_copy(t_process *process);

/*
**	Utils.
*/

int				to_little_endian32(int val);

/*
**	Instruction utils.
*/

t_bool			is_valid_reg(int reg_id);
int				sizeof_param_type(t_arg_type type);
void			param_at(t_instruction *inst, int pos, t_arg_type type, void *res);

/*
**	load_params.c
*/

t_bool			load_params(t_op *op, t_instruction *inst, t_paraminfo *paraminfo);

/*
**	Instructions processing.
*/

extern	void	(*g_op_func_tab[])(t_corewar*, t_process*, t_paraminfo*);

void			inst_live(t_corewar *corewar, t_process *process, t_paraminfo*);
void			inst_ld(t_corewar *corewar, t_process *process, t_paraminfo*);
void			inst_st(t_corewar *corewar, t_process *process, t_paraminfo*);
void			inst_add(t_corewar *corewar, t_process *process, t_paraminfo*);
void			inst_sub(t_corewar *corewar, t_process *process, t_paraminfo*);
void			inst_and(t_corewar *corewar, t_process *process, t_paraminfo*);
void			inst_or(t_corewar *corewar, t_process *process, t_paraminfo*);
void			inst_xor(t_corewar *corewar, t_process *process, t_paraminfo*);
void			inst_zjmp(t_corewar *corewar, t_process *process, t_paraminfo*);
void			inst_ldi(t_corewar *corewar, t_process *process, t_paraminfo*);
void			inst_sti(t_corewar *corewar, t_process *process, t_paraminfo*);
void			inst_fork(t_corewar *corewar, t_process *process, t_paraminfo*);
void			inst_lld(t_corewar *corewar, t_process *process, t_paraminfo*);
void			inst_lldi(t_corewar *corewar, t_process *process, t_paraminfo*);
void			inst_lfork(t_corewar *corewar, t_process *process, t_paraminfo*);
void			inst_aff(t_corewar *corewar, t_process *process, t_paraminfo*);

#endif
