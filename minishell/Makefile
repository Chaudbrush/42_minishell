# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vloureir <vloureir@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/11 09:44:49 by vloureir          #+#    #+#              #
#    Updated: 2025/07/16 16:54:51 by vloureir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ifndef VERBOSE
# MAKEFLAGS += --silent
# endif

NAME := minishell

SRC := $(wildcard *.c)

OBJ := $(SRC:.c=.o)

VAL := --leak-check=full --show-leak-kinds=all --track-origins=yes --show-reachable=yes --suppressions=readline.supp

LFLAG := -lreadline

all: $(NAME)

$(NAME): $(OBJ)
	rm -f $(NAME)
	cc $(OBJ) -o $(NAME) $(LFLAG)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all