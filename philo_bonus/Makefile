# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: obenchkr <obenchkr@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/29 21:05:41 by obenchkr          #+#    #+#              #
#    Updated: 2024/05/09 14:54:36 by obenchkr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra -Iinc
CLIBS		=	-lpthread

NAME		=	philo_bonus
SRC_FILES	=	actions_bonus.c cleanup_bonus.c errors_bonus.c init_bonus.c \
				main_bonus.c simulation_bonus.c utils_bonus.c
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
