# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msoler-e <msoler-e@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/29 11:33:17 by msoler-e          #+#    #+#              #
#    Updated: 2022/11/28 11:46:41 by msoler-e         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC		= main.c num.c philo.c string.c util.c list.c time.c

DIR		= libft/

NAME	= philo

OBJS	= ${SRC:.c=.o}

CC		= 	gcc

RM		= 	rm -f

CFLAGS =	-Wall -Werror -Wextra

%.o:%.c
			${CC} -I ${DIR} -c $< -o $@

all:	${NAME}

${NAME}:	${OBJS} philo.h
			$(CC) $(OBJS) $(CFLAGS) -o $(NAME)

clean:
			${RM} ${OBJS} 
			${RM} ${NAME}

fclean:		clean

re:	fclean $(NAME)

.PHONY: all clean fclean re
