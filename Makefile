
SRCS=		main.c \
			./parsing/env_utils.c \
			./parsing/garbage_collector.c \
			./parsing/expanding.c \
			./parsing/removing_quotes.c \
			./parsing/files_parsing.c \
			./parsing/cmd_parsing.c \
			./parsing/general_utils1.c \
			./parsing/general_utils2.c \
			./parsing/parse_tree.c \
			./parsing/parse_tree_utils.c \
			./parsing/tokenization1.c \
			./parsing/tokenization2.c \
			./parsing/display_parse_tree.c \
			./parsing/ambiguous_redirections.c \
			./parsing/utils_without_garbage_collection.c \
			./parsing/queue_utils.c \
			./parsing/here_doc.c \
			./parsing/init.c \
			./parsing/signals.c \
			./execution/ft_execvp.c \
			./execution/ft_execvp_utils.c \
			./execution/ft_execvp_utils1.c \
			./execution/execute.c \
			./execution/exec_utils.c \
			./execution/buildsin_check.c \
			./execution/redirections.c \
			./execution/build-ins/buildins_utils.c \
			./execution/build-ins/ft_cd.c \
			./execution/build-ins/ft_pwd.c \
			./execution/build-ins/ft_echo.c \
			./execution/build-ins/ft_env.c \
			./execution/build-ins/ft_exit.c \
			./execution/build-ins/ft_export.c \
			./execution/build-ins/ft_unset.c

OBJS =		${SRCS:.c=.o}

NAME =	minishell
CC = cc 
CFLAGS = -Wall -Wextra -Werror
CFLAGS += -fsanitize=address -g
CFLAGS += -I/Users/okhiar/goinfre/brew/opt/readline/include/
RDLIB = -lreadline -L/Users/okhiar/goinfre/brew/opt/readline/lib/
RM= rm -f
LIBFT = make -C ./libft
LIBAR = ./libft/libft.a

%.o: %.c
	@${CC} ${CFLAGS} -c $^ -o $@

all: ${NAME}

${NAME}: ${OBJS}
	@${LIBFT}
	@${CC} ${CFLAGS} ${RDLIB} ${LIBAR} ${OBJS} -o ${NAME}

clean:
	@make clean -C ./libft
	@${RM} ${OBJS}

fclean: clean
	@make fclean -C ./libft
	@${RM} ${NAME}

re: fclean all

run: re
	@./${NAME}