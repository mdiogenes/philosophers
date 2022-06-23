# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msoler-e <msoler-e@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/23 12:38:24 by msoler-e          #+#    #+#              #
#    Updated: 2022/06/23 13:24:43 by msoler-e         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_FILES		=	main.c \
SRCS_DIR		=	srcs
OBJS_DIR		=	obj
OBJS_SUBS		= 	obj \
SRCS 			=	$(addprefix $(SRCS_DIR)/,$(SRCS_FILES))
OBJS			=	$(addprefix $(OBJS_DIR)/,$(SRCS_FILES:.c=.o))
CC				=	gcc
RM				= 	rm -rf
CFLAGS			=	-Wall -Wextra -Werror
HEADER			=	philo.h
HEADER_DIR		=	inc
NAME			=	philo


all: $(OBJS_SUBS) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS)$(CFLAGS) $(NAME)


$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADER_DIR)/$(HEADER)
	$(CC) $(CFLAGS)-c $< -o $@

$(OBJS_SUBS):
	-mkdir $(OBJS_SUBS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(OBJS_SUBS)

re:	fclean $(OBJS_SUBS) $(NAME)

.PHONY: all clean fclean re
