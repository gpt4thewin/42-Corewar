/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbakhti <mbakhti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 14:53:26 by mbakhti           #+#    #+#             */
/*   Updated: 2019/03/13 14:30:44 by mbakhti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct		s_bytecode
{
	t_header		header;
	char			*program;
}					t_bytecode;

typedef struct		s_lab
{
	int				op_number;
	t_token			label;
	int				offset;
	struct s_lab	*next;
}					t_lab;

typedef struct		s_instr
{
	int				op_number;
	int				size;
	t_token			op;
	t_token			param[MAX_ARGS_NUMBER];
	char			opcode;
	char			argcode;
	int				arg[MAX_ARGS_NUMBER];
	struct s_instr	*next;
}					t_instr;

void				parse_tokens(t_bytecode *bytecode, t_token *tokens);
void				generate_header(t_header *header, t_token **current);
void				check_syntax(t_token *token, t_lab **labels,
t_instr **instructions);
void				push_instruction(t_token **token, t_instr **last);
void				generate_program(t_bytecode *bytecode, t_lab **labels,
t_instr **instructions);
void				check_instructions(t_instr **instructions, t_lab *labels);
void				check_parameters(t_instr **op, t_lab *labels);
void				write_instructions(t_bytecode *bytecode,
t_instr *instructions);
void				copy_token(t_token src, t_token *dst);
int					get_type_size(t_instr **op, int i);
int					get_current_offset(t_instr current, t_instr *instructions);
int					get_label_offset(char *label_name, t_lab *labels);
void				display_faulty_token(t_token token);
void				syntax_error(t_token token);
void				invalid_instruction_error(t_token token);
void				invalid_parameter_error(int i, t_instr op);
void				invalid_label_error(char *label, t_token token);
void				invalid_parameter_count(t_instr op);

#endif
