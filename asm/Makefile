# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbakhti <mbakhti@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/18 20:20:33 by mbakhti           #+#    #+#              #
#    Updated: 2019/03/09 16:37:26 by mbakhti          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= asm

CM_SOURCES	= op.c
CM_SRCS_DR	= ../commons
CM_SRCS		= $(addprefix $(CM_SRCS_DR)/, $(CM_SOURCES))

SOURCES		+= asm.c\
			check_arguments.c\
			store_assembly.c\
			compile_champion.c
SOURCES		+= $(addprefix lexer/, \
			lexer.c\
			tokenizer.c\
			is_whitespace.c\
			is_endline.c\
			is_separator.c\
			is_comment.c\
			is_command.c\
			is_string.c\
			is_label.c\
			is_register.c\
			is_indirect.c\
			is_indirect_label.c\
			is_direct.c\
			is_direct_label.c\
			is_instruction.c)
SOURCES		+= $(addprefix parser/, \
			parser.c\
			generate_header.c\
			check_syntax.c\
			push_instruction.c\
			generate_program.c\
			check_instructions.c\
			check_parameters.c\
			write_instructions.c\
			parser_errors.c\
			parser_tools.c)
SRCS_DR		= srcs
SRCS		= $(addprefix $(SRCS_DR)/, $(SOURCES))

CC			= gcc
CFLAGS		= -Wall -Werror -Wextra -I ../libft/includes -I ../commons -I incs

OBJS_DR		= objs
OBJS		= $(SRCS:$(SRCS_DR)/%.c=$(OBJS_DR)/%.o)

CM_OBJS_DR	= ../commons/objs
CM_OBJS		= $(CM_SRCS:$(CM_SRCS_DR)/%.c=$(CM_OBJS_DR)/%.o)

LIBFT_DR	= ../libft
LIBFT		= $(LIBFT_DR)/libft.a
LIBFT_FLAG	= -L$(LIBFT_DR) -lft

RESET		= \e[0m
ITALIC		= \e[3m
RED			= \e[31m
GREEN		= \e[32m
YELLOW		= \e[33m
BLUE		= \e[34m
MAGENTA		= \e[35m

all : $(NAME)

$(NAME) : $(LIBFT) $(OBJS_DR) $(OBJS) $(CM_OBJS)
	@ $(CC) $(CFLAGS) $(OBJS) $(CM_OBJS) $(LIBFT_FLAG) -o $@
	@ printf "$(GREEN)%-42s$(RESET)\n" "Build $@ binary"

$(LIBFT) :
	@ printf "$(MAGENTA)%-42s$(RESET)\r" "Compiling $@"
	@ make -sC $(LIBFT_DR)
	@ printf "$(MAGENTA)%-42s$(RESET)\n" "Build $@ library"

$(OBJS_DR) :
	@ mkdir -p $(OBJS_DR) $(OBJS_DR)/lexer $(OBJS_DR)/parser
	@ mkdir -p $(CM_OBJS_DR)

$(OBJS_DR)/%.o : $(SRCS_DR)/%.c
	@ $(CC) $(CFLAGS) -o $@ -c $<
	@ printf "$(ITALIC)$(BLUE)%-42.42s$(RESET)\r" "Compiled $@"

$(CM_OBJS_DR)/%.o : $(CM_SRCS_DR)/%.c
	@ $(CC) $(CFLAGS) -o $@ -c $<
	@ printf "$(ITALIC)$(BLUE)%-42.42s$(RESET)\r" "Compiled $@"

clean :
	@ make -sC $(LIBFT_DR) clean
	@ rm -rf $(OBJS_DR)
	@ rm -rf $(CM_OBJS_DR)
	@ printf "$(YELLOW)%-42s$(RESET)\n" "Removed $(NAME) $(OBJS_DR)"

fclean : clean
	@ make -sC $(LIBFT_DR) fclean
	@ rm -f $(NAME)
	@ printf "$(YELLOW)%-42s$(RESET)\n" "Removed $(NAME) binary"

re : fclean all

norme :
	@ norminette `find . -type f \( -name *.c -o -name *.h \)` \
	| if ! grep Error -B 1 --color; then printf "$(GREEN)NORME OK$(RESET)\n"; fi

.PHONY: all clean fclean re norme
