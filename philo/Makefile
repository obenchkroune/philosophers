# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/28 09:45:12 by obenchkr          #+#    #+#              #
#    Updated: 2024/05/01 00:58:19 by obenchkr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra -Iinc
CLIBS		=	-lpthread

NAME		=	philo
SRC_FILES	=	actions.c checkers.c cleanup.c errors.c init.c main.c \
				simulation.c utils.c
SRC			=	$(addprefix src/, $(SRC_FILES))
OBJ			=	$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ $(CLIBS) -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

.SECONDARY: $(OBJ)
