# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbakhti <mbakhti@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/18 20:21:38 by mbakhti           #+#    #+#              #
#    Updated: 2019/04/10 19:25:11 by agoulas          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= Manager
ASM_NAME	= asm
ASM_DIR		= asm
ASM			= $(ASM_DIR)/$(ASM_NAME)

VM_DIR		= vm
VM_NAME		= corewar
VM 			= $(VM_DIR)/$(VM_NAME)

all : $(ASM) $(VM)

$(ASM) :
	@make -sC $(ASM_DIR)

$(VM) :
	@make -sC $(VM_DIR)

clean :
	@make -sC $(ASM_DIR) clean
	@make -sC $(VM_DIR) clean

fclean :
	@make -sC $(ASM_DIR) fclean
	@make -sC $(VM_DIR) fclean

re : fclean all

norme :
	@norminette `find . -type f \( -name *.c -o -name *.h \)` \
	| if ! grep Error -B 1 --color; then printf "NORME OK\n"; fi

.PHONY : all clean fclean re test norme $(ASM) $(VM)
