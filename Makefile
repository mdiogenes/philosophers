# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msoler-e <msoler-e@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/29 11:33:17 by msoler-e          #+#    #+#              #
#    Updated: 2022/09/14 10:16:01 by msoler-e         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC		= main.c numbers.c philo.c strings.c utils.c lists.c time.c

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
