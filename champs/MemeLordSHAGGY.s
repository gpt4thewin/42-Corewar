# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    MemeLordSHAGGY.s                                   :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agoulas <agoulas@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/08 16:11:59 by agoulas           #+#    #+#              #
#    Updated: 2019/03/14 15:46:19 by agoulas          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.name "MemeLord Shaggy"
.comment "Zoinks! i used only 10% of my power..."

start:
		sti r1, %:live, %1
		zjmp	%:live

attack:
		sti r1, 1, %1
		st r1, r2
		st r1, r3
		st r1, r5
		st r1, r3
		st r1, r4
		st r1, r5
		st r1, r6
		st r1, r7
		st r1, r8
		st r1, r9
		st r1, r10
		st r1, r11
		st r1, r12
		st r1, r13
		st r1, r14
		st r1, r15
		st r1, r16
		sti r1, r2, %1
		zjmp %:live

live:
		live %0
		live %1
		live %2
		live %3
		live %4
		live %5
		live %6
		live %7
		live %8
		live %9
		live %10
		live %11
		live %12
		live %13
		live %14
		live %15
		live %16
		 zjmp %:attack
