CC = gcc
CFLAGS = -Wall -Wextra -Werror
CFLAGS += -g

NAME = philo

DIR_H = ./includes/
DIR_S = ./srcs/
DIR_O = ./

SRC = main.c		\

SRCS = $(addprefix $(DIR_S), $(SRC))

OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean all re