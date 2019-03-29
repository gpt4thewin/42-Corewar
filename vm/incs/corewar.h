/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juazouz <juazouz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:46:43 by mbakhti           #+#    #+#             */
/*   Updated: 2019/03/29 14:44:14 by juazouz          ###   ########.fr       */
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

# define DUMP_WIDTH 64
# define MSG_COMMAND_LINE_ERROR "Error: invalid command line."
# define VERBOSE_DEATH	0x01
# define VERBOSE_LIVE	0x02
# define VERBOSE_INST	0x04
# define VERBOSE_AFF	0x08

typedef struct s_player			t_player;
typedef struct s_process		t_process;
typedef struct s_corewar		t_corewar;
typedef struct s_arguments		t_arguments;
typedef struct s_instruction	t_instruction;
typedef union u_paramval		t_paramval;
typedef struct s_memaccess		t_memaccess;
typedef enum e_color			t_color;
typedef struct s_paraminfo		t_paraminfo;
typedef struct s_param			t_param;

typedef int						t_reg;
typedef short					t_ind;
typedef int						t_dir;

/*
**	Union of all parameters types of varying size.
*/

union			u_paramval
{
	char		reg_id;
	t_ind		ind;
	t_dir		dir;
};

/*
**	Instruction type and value.
*/

struct			s_param
{
	t_arg_type	type;
	t_paramval	value;
};

struct			s_paraminfo
{
	char			args_number;
	t_param			params[MAX_ARGS_NUMBER];
};

/*
**	Enum of color for print dump.
*/

enum			e_color
{
	WHITE,
	BLUE,
	GREEN,
	RED,
	YELLOW
};

/*
**	Player.
*/

struct			s_player
{
	int			id;
	t_color		color;
	int			last_check;
	const char	*file;
	size_t		prog_size;
	char		comment[COMMENT_LENGTH + 1];
	char		prog_name[PROG_NAME_LENGTH + 1];
	char		program[CHAMP_MAX_SIZE];
};

/*
**	Virtual machine task / thread / process.
*/

struct			s_process
{
	int			id;
	t_player	*player;
	int			exec_cycle;
	int			pc;
	t_reg		reg[REG_NUMBER];
	t_bool		carry;
	t_op		*op;
	t_paraminfo	paraminfo;
	t_bool		is_jump;
	int			nbr_live;
};

/*
**	Program command line arguments.
*/

struct			s_arguments
{
	int			dump_nbr_cycle;
	t_bool		dump_cycle;
	t_bool		dump_colors;
	int			verbosity;
	t_bool		usage;
};

/*
**	Corewar virtual machine.
*/

struct			s_corewar
{
	t_arguments	arguments;
	int			curr_cycle;
	int			next_check_cycle;
	int			players_count;
	t_player	players[MAX_PLAYERS];
	t_player	*last_live;
	int			cycle_to_die;
	int			checks_count;
	int			total_nbr_live;
	int			process_count;
	t_list		*processes;
	t_color		map_memory_color[MEM_SIZE];
	char		memory[MEM_SIZE];
};

/*
**	Generic memory read/write information.
**	Contains both parameters and result.
*/

struct			s_memaccess
{
	t_process	*process;
	t_bool		idxmod;
	size_t		value_size;
	t_param		m_param;
	int			m_value;
};

/*
**	Byte code instruction with parameters.
*/

struct			s_inst_param
{
	unsigned char	arg_type_4:2;
	unsigned char	arg_type_3:2;
	unsigned char	arg_type_2:2;
	unsigned char	arg_type_1:2;
	char			parameters[0];
};

union			u_inst_param
{
	t_dir				single_dir;
	struct s_inst_param	multi;
	char				debug8;
	char				debug16;
};

struct			s_instruction
{
	char				opcode;
	union u_inst_param	param;
} __attribute__((packed,aligned(1)));

/*
**	Corewar.
*/

int				kill_dead_process(t_corewar *corewar);
void			check_alive(t_corewar *corewar);
t_corewar		*corewar_new(void);
t_player		*corewar_run(t_corewar *corewar);
void			corewar_die(char *msg);
void			corewar_add_process(t_corewar *corewar, t_process *process);
t_reg			corewar_reg_read(t_corewar *corewar, int pc, int addr);
void			corewar_reg_write(t_corewar *corewar, int pc, int addr,
	t_reg val);

/*
**	Memory.
*/

int				generic_read(t_corewar *corewar, t_memaccess *memaccess,
	t_param param);
void			generic_write(t_corewar *corewar, t_memaccess *memaccess,
	t_param param, int val);

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
void			players_init_id(t_corewar *corewar);
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
void			process_set_reg(t_process *process, char reg_id, t_reg val);
t_reg			process_get_reg(t_process *process, char reg_id);

/*
**	utils.c
*/

int				get_physical_addr(int addr);
t_bool			is_valid_reg(int reg_id);
int				sizeof_param_type(t_arg_type type);
t_op			*get_op(int opcode);
void			param_at(t_instruction *inst, int pos, t_arg_type type,
	void *res);

/*
**	load_params.c
*/

t_bool			load_params(t_op *op, t_instruction *inst,
	t_paraminfo *paraminfo);

/*
**	LOad color on the map_memory_color.
*/

void			*memcpy_color(t_corewar *corewar, t_player *player, size_t num,
	size_t pos);

/*
**	Instructions processing.
*/

extern	void	(*g_op_func_tab[])(t_corewar*, t_process*, t_paraminfo*);

void			inst_live(t_corewar *corewar, t_process *process,
t_paraminfo *paraminfo);
void			inst_ld(t_corewar *corewar, t_process *process,
t_paraminfo *paraminfo);
void			inst_st(t_corewar *corewar, t_process *process,
	t_paraminfo *paraminfo);
void			inst_add(t_corewar *corewar, t_process *process,
	t_paraminfo *paraminfo);
void			inst_sub(t_corewar *corewar, t_process *process,
	t_paraminfo *paraminfo);
void			inst_and(t_corewar *corewar, t_process *process,
	t_paraminfo *paraminfo);
void			inst_or(t_corewar *corewar, t_process *process,
	t_paraminfo *paraminfo);
void			inst_xor(t_corewar *corewar, t_process *process,
	t_paraminfo *paraminfo);
void			inst_zjmp(t_corewar *corewar, t_process *process,
	t_paraminfo *paraminfo);
void			inst_ldi(t_corewar *corewar, t_process *process,
	t_paraminfo *paraminfo);
void			inst_sti(t_corewar *corewar, t_process *process,
	t_paraminfo *paraminfo);
void			inst_fork(t_corewar *corewar, t_process *process,
	t_paraminfo *paraminfo);
void			inst_lld(t_corewar *corewar, t_process *process,
	t_paraminfo *paraminfo);
void			inst_lldi(t_corewar *corewar, t_process *process,
	t_paraminfo *paraminfo);
void			inst_lfork(t_corewar *corewar, t_process *process,
	t_paraminfo *paraminfo);
void			inst_aff(t_corewar *corewar, t_process *process,
	t_paraminfo *paraminfo);

/*
**	print_instruction.c
*/

void			print_instruction(t_process *process);

void			print_start_fight(t_corewar *corewar);

#endif
