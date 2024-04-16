# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/29 21:05:41 by obenchkr          #+#    #+#              #
#    Updated: 2024/04/16 00:07:34 by obenchkr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=	cc
CFLAGS	=	-Wall -Werror -Wextra -Iinc
CLIBS	=	-lpthread

NAME	=	philo_bonus
SRC		=	./src/cleanup_bonus.c ./src/utils_bonus.c ./src/philosophers_bonus.c \
			./src/main_bonus.c ./src/actions_bonus.c ./src/errors_bonus.c ./src/init_bonus.c
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
