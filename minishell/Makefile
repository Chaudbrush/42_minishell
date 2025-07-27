# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zali <zali@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/11 09:44:49 by vloureir          #+#    #+#              #
#    Updated: 2025/07/27 17:29:46 by zali             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ifndef VERBOSE
# MAKEFLAGS += --silent
# endif

NAME := minishell
RUN_CMD := $(wildcard runcmd/*.c)
EXPAN_CMD := $(wildcard expansion/*.c)
SRC := $(wildcard *.c)
OBJ := $(SRC:.c=.o) $(RUN_CMD:.c=.o) $(EXPAN_CMD:.c=.o)

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
