# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fwong <fwong@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/25 15:53:23 by fwong             #+#    #+#              #
#    Updated: 2022/07/25 01:37:48 by fwong            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	pipex

CC		=	clang

CFLAGS	=	-Wall -Wextra -Werror -pthread -MMD -MP -I ./includes -g3

LIB		=	-Llibft/ -lft

SRCS	= 	parsing.c	\
			utils.c		\
			find_cmd.c	\

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
