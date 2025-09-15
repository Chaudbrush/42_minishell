ifndef VERBOSE
MAKEFLAGS += --silent
endif

NAME := minishell

SRC := main.c safe_utils.c

BUILTIN := $(addprefix builtin/, builtin.c cd.c echo.c env.c exit.c export_sort.c \
			export_utils.c export.c pwd.c quote_split.c split_utils.c unset.c)

ENVP := $(addprefix envp/, envp_utils.c envp.c list_utils.c)

EXECUTE := $(addprefix execute/, execute_utils.c execute.c \
			heredoc_expansion.c mod_split.c recursive_help.c)

EXPAN_CMD := $(addprefix expansion/, argv_merge.c copy_expansion.c \
			expansion_utils.c expansion.c get_expansion_len.c)
		
PARSE := $(addprefix parse/, parse_correction.c parse_free.c parse.c \
			parse_utils.c struct_inits.c token_errors.c tokens.c)

READLINE := $(addprefix readline/, peek_token.c readline.c)

RUN_CMD := $(addprefix runcmd/, runcmd.c builtin_exec.c)

SIGNAL := $(addprefix signals/, signals.c)

OBJ := $(SRC:.c=.o) $(ENVP:.c=.o) $(SIGNAL:.c=.o) $(RUN_CMD:.c=.o) $(BUILTIN:.c=.o) \
			$(READLINE:.c=.o) $(EXPAN_CMD:.c=.o) $(EXECUTE:.c=.o) $(PARSE:.c=.o)

HEADER := $(addprefix includes/, builtin.h cmd_struct.h envp.h execute.h \
			expansion.h minishell.h parse.h readline.h runcmd.h signals.h)

INC := -Iincludes

# VAL := --leak-check=full --show-leak-kinds=all --track-origins=yes --show-reachable=yes \
			--trace-children=yes --track-fds=all --suppressions=readline.supp

VAL := --leak-check=full --show-leak-kinds=all --track-origins=yes \
			--show-reachable=yes --track-fds=all --suppressions=readline.supp

CFLAGS := -Wall -Werror -Wextra -g

LFLAG := -lreadline -Llibft -lft

CC := cc

RM := rm -f

RED := \033[1;30;41m

GREEN := \033[1;30;42m

OFF := \033[0m

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	$(MAKE) -C ./libft
	$(CC) $(OBJ) $(CFLAGS) -o $(NAME) $(LFLAG) $(INC)
	@echo "$(GREEN) Minishell Crated $(OFF)"

clean:
	$(RM) $(OBJ)
	$(MAKE) -C ./libft clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C ./libft fclean
	@echo "$(RED) Minishell Deleted $(OFF)"

re: fclean all

valrun: $(NAME)
	valgrind $(VAL) ./$(NAME)

.PHONY: all clean fclean re valrun
