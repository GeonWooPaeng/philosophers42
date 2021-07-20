# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gpaeng <gpaeng@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/05 12:11:44 by gpaeng            #+#    #+#              #
#    Updated: 2021/07/10 23:52:13 by gpaeng           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wextra -Werror -Wall
CFLAGS += -g

NAME = philo

DIR_H = ./includes/
DIR_S = ./srcs/
DIR_O = ./

SRC =	ft_utils.c	\
		ft_init.c	\
		main.c		\

SRCS = $(addprefix $(DIR_S), $(SRC))

OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lpthread

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean all re