# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zali <zali@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/11 09:44:49 by vloureir          #+#    #+#              #
#    Updated: 2025/08/16 19:42:32 by zali             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#ifndef VERBOSE
#MAKEFLAGS += --silent
#endif

NAME := minishell

SRC := $(wildcard *.c)
ENVP := $(wildcard envp/*.c)
SIGNAL := $(wildcard signals/*.c)
RUN_CMD := $(wildcard runcmd/*.c)
EXECUTE := $(wildcard execute/*.c)
PARSE := $(wildcard parse/*.c)
BUILTIN := $(wildcard builtin/*.c)
READLINE := $(wildcard readline/*.c)
EXPAN_CMD := $(wildcard expansion/*.c)

OBJ := $(SRC:.c=.o) $(ENVP:.c=.o) $(SIGNAL:.c=.o) $(RUN_CMD:.c=.o) $(BUILTIN:.c=.o) $(READLINE:.c=.o) $(EXPAN_CMD:.c=.o) $(EXECUTE:.c=.o) $(PARSE:.c=.o)

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
