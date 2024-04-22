
SRCS=		main.c \
			parsing/env_utils.c \
			parsing/garbage_collector.c \
			parsing/syntax_errors.c \
			parsing/expanding.c \
			parsing/removing_quotes.c \
			parsing/files_parsing.c \
			parsing/cmd_parsing.c \
			parsing/general_utils1.c \
			parsing/general_utils2.c \
			parsing/general_utils3.c \
			parsing/parse_tree.c \
			parsing/parse_tree_utils.c \
			parsing/tokenization1.c \
			parsing/tokenization2.c \
			parsing/tokenization3.c \
			parsing/display_parse_tree.c \
			parsing/ambiguous_redirections.c \
			parsing/args_files_separation.c \
			parsing/utils_without_garbage_collection.c \
			parsing/queue_utils.c \
			parsing/here_doc.c \
			parsing/init.c \
			parsing/signals.c \
			./execution/ft_execvp.c \
			./execution/ft_execvp_utils.c \
			./execution/execute.c \
			./execution/exec_utils.c \
			./execution/exec_utils2.c \
			./execution/buildsin_check.c \
			./execution/buildins_exec.c \
			./execution/redirections.c \
			./execution/redirection_utils.c \
			./execution/global_utils.c \
			./execution/wildcards.c \
			./execution/apply_wildcards.c \
			./execution/built-ins/buildins_utils.c \
			./execution/built-ins/ft_cd.c \
			./execution/built-ins/ft_pwd.c \
			./execution/built-ins/ft_echo.c \
			./execution/built-ins/ft_env.c \
			./execution/built-ins/ft_exit.c \
			./execution/built-ins/ft_export.c \
			./execution/built-ins/ft_unset.c

OBJS =		${SRCS:.c=.o}

NAME =	minishell
CC = cc 
CFLAGS = -Wall -Wextra -Werror
# CFLAGS += -fsanitize=address -g
# ? OMAR
# CFLAGS += -I/Users/obednaou/brew/opt/readline/include/
# RDLIB = -lreadline -L/Users/obednaou/brew/opt/readline/lib/
# ? OUSSAMA
# CFLAGS += -I/Users/okhiar/goinfre/brew/opt/readline/include/
# RDLIB = -lreadline -L/Users/okhiar/goinfre/brew/opt/readline/lib/
RM= rm -f
LIBFT = make -C ./libft
# LIBAR = ./libft/libft.a

# Path to the Readline library and include directory
# READLINE_INCLUDE_DIR = /usr/include/readline
# READLINE_LIB_DIR = /usr/lib/x86_64-linux-gnu

# Compiler flags
CFLAGS += -Ilibft
# Linker flags
LDFLAGS += -lreadline -lft -Llibft

%.o: %.c
	@${CC} ${CFLAGS} -c $^ -o $@

all: ${NAME}

${NAME}: ${OBJS}
	@${LIBFT}
	@${CC} ${CFLAGS} ${OBJS} ${LDFLAGS} -o ${NAME}

clean:
	@make clean -C ./libft
	@${RM} ${OBJS}

fclean: clean
	@make fclean -C ./libft
	@${RM} ${NAME}

re: fclean all

run: re
	@./${NAME}