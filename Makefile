# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fwong <fwong@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/29 01:14:57 by fwong             #+#    #+#              #
#    Updated: 2023/01/29 01:14:57 by fwong            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo

CC		=	clang

CFLAGS	=	-Wall -Wextra -Werror -pthread -MMD -MP -I ./includes -g3

LIB		=	-Llibft/ -lft

SRCS	= 	fork.c		\
			init.c		\
			main.c		\
			output.c	\
			parsing.c	\
			utils.c

OBJS	:=	${addprefix ./objs/,${SRCS:%.c=%.o}}

DEP		=	$(addprefix ./objs/,$(OBJS:%.o=%.d))

all: ${NAME}

-include $(DEP)

./objs/%.o: src/%.c
	@@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ -c $<

${NAME}: ${OBJS} ./libft/libft.a
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIB)

./libft/libft.a:
	make $(@F) -C $(@D)

clean:
	rm -rf obj/
	rm -f ${OBJS}
	make $@ -C ./libft/

fclean: 
	rm -rf obj/
	rm -f ${NAME}
	make $@ -C libft

re:	fclean all

.PHONY: all clean fclean re
