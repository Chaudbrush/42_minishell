# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vloureir <vloureir@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/12 20:29:48 by vloureir          #+#    #+#              #
#    Updated: 2025/08/31 18:18:21 by vloureir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifndef VERBOSE
MAKEFLAGS += --silent
endif

NAME := libft.a

CC := cc

CFLAGS := -Wall -Wextra -Werror

SRC := src/ft_isalpha.c src/ft_isdigit.c src/ft_isalnum.c src/ft_isascii.c \
		src/ft_isprint.c src/ft_strlen.c src/ft_memset.c src/ft_bzero.c \
		src/ft_memcpy.c src/ft_memmove.c src/ft_strlcpy.c src/ft_strlcat.c \
		src/ft_toupper.c src/ft_tolower.c src/ft_strchr.c src/ft_strrchr.c \
		src/ft_strncmp.c src/ft_strcmp.c src/ft_memchr.c src/ft_memcmp.c \
		src/ft_strnstr.c src/ft_atoi.c src/ft_calloc.c src/ft_strdup.c \
		src/ft_substr.c src/ft_strjoin.c src/ft_strtrim.c src/ft_split.c \
		src/ft_itoa.c src/ft_strmapi.c src/ft_striteri.c src/ft_putchar_fd.c \
		src/ft_putstr_fd.c src/ft_putendl_fd.c src/ft_putnbr_fd.c \
		src/ft_atol.c src/ft_atoll.c src/ft_strndup.c src/ft_isspace.c

OBJ := $(SRC:.c=.o)

SRC_BONUS := src/ft_lstnew.c src/ft_lstadd_front.c src/ft_lstsize.c \
			src/ft_lstlast.c src/ft_lstadd_back.c src/ft_lstdelone.c \
			src/ft_lstclear.c src/ft_lstiter.c src/ft_lstmap.c

OBJ_BONUS := $(SRC_BONUS:.c=.o)

INC := -Iincludes

HEADER := includes/libft.h

AR := ar -rcs

RM := rm -f

RED := \033[1;30;41m

GREEN := \033[1;30;42m

OFF := \033[0m

all: $(NAME)

$(NAME): $(OBJ) $(OBJ_BONUS)
	$(AR) $@ $^
	@echo "$(GREEN) Library Crated $(OFF)"

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -o $@ -c $< $(INC)

bonus: $(OBJ) $(OBJ_BONUS)
	$(AR) $(NAME) $(OBJ) $(OBJ_BONUS)
	@echo "$(GREEN) Library Crated $(OFF)"
	touch bonus

clean:
	$(RM) $(OBJ) $(OBJ_BONUS)

fclean: clean
	$(RM) $(NAME)
	$(RM) bonus
	@echo "$(RED) Library Deleted $(OFF)"

re: fclean all
