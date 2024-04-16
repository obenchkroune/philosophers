# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/28 09:45:12 by obenchkr          #+#    #+#              #
#    Updated: 2024/04/16 00:06:21 by obenchkr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=	cc
CFLAGS	=	-Wall -Werror -Wextra -Iinc -fsanitize=thread -g3
CLIBS	=	-lpthread

NAME	=	philo
SRC		=	src/actions.c src/cleanup.c src/errors.c src/init.c src/main.c src/philosopher.c src/utils.c src/atomic_checkers.c
OBJ		=	$(SRC:.c=.o)

all: $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ $(CLIBS) -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

.SECONDARY: $(OBJ)
