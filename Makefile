# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vloureir <vloureir@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/11 09:44:49 by vloureir          #+#    #+#              #
#    Updated: 2025/07/30 15:29:24 by vloureir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ifndef VERBOSE
# MAKEFLAGS += --silent
# endif

NAME := minishell

SRC := $(wildcard *.c)
ENVP := $(wildcard envp/*.c)
SIGNAL := $(wildcard signals/*.c)
RUN_CMD := $(wildcard runcmd/*.c)
BUILTIN := $(wildcard builtin/*.c)
EXPAN_CMD := $(wildcard expansion/*.c)

OBJ := $(SRC:.c=.o) $(ENVP:.c=.o) $(SIGNAL:.c=.o) $(RUN_CMD:.c=.o) $(BUILTIN:.c=.o) $(EXPAN_CMD:.c=.o)

VAL := --leak-check=full --show-leak-kinds=all --track-origins=yes --show-reachable=yes --suppressions=readline.supp

CFLAGS := -Wall -Werror -Wextra -g

LFLAG := -lreadline -Llibft -lft

all: $(NAME)

valrun: $(NAME)
	valgrind $(VAL) ./$(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C ./libft
	cc $(OBJ) $(CFLAGS) -o $(NAME) $(LFLAG)

clean:
	rm -f $(OBJ)
	$(MAKE) -C ./libft clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C ./libft fclean

re: fclean all
