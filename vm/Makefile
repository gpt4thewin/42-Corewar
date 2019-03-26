# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juazouz <juazouz@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/18 20:20:33 by mbakhti           #+#    #+#              #
#    Updated: 2019/03/26 19:00:49 by juazouz          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= corewar

SOURCES		+=	main.c \
				corewar.c \
				corewar_run.c \
				corewar_dead_or_live.c \
				map_memory_color.c \
				memory.c \
				arg_utils.c \
				instructions/instructions_core.c \
				instructions/instructions_math.c \
				instructions/instructions_logic.c \
				instructions/instructions_mem.c \
				instructions/instructions_mem_long.c \
				load_params.c \
				parse_parameters.c \
				parse_parameters_id.c \
				setup_players.c \
				process.c \
				player.c \
				dump.c \
				endian_utils.c

SRCS_DR		= srcs
SRCS		= $(addprefix $(SRCS_DR)/, $(SOURCES))

CM_SOURCES	= op.c convert_endian32.c
CM_SRCS_DR	= ../commons
CM_SRCS		= $(addprefix $(CM_SRCS_DR)/, $(CM_SOURCES))

CC			= gcc
CFLAGS		= -Wall -Werror -Wextra -I ../libft/includes -I ../commons -I incs -g

DEPS		= incs/corewar.h Makefile
OBJS_DR		= objs
OBJS		= $(SRCS:$(SRCS_DR)/%.c=$(OBJS_DR)/%.o)

CM_DEPS		= ../commons/op.h Makefile
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
	@ mkdir -p $(OBJS_DR)
	@ mkdir -p $(CM_OBJS_DR)

$(OBJS_DR)/%.o : $(SRCS_DR)/%.c $(DEPS)
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) -o $@ -c $<
	@ printf "$(ITALIC)$(BLUE)%-42.42s$(RESET)\r" "Compiled $@"

$(CM_OBJS_DR)/%.o : $(CM_SRCS_DR)/%.c $(CM_DEPS)
	@ mkdir -p $(dir $@)
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
