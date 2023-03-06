
SRCS=		main.c \
			env_utils.c \
			garbage_collector.c \
			syntax_errors.c \
			expanding.c \
			removing_quotes.c \
			files_parsing.c \
			cmd_parsing.c \
			general_utils1.c \
			general_utils2.c \
			general_utils3.c \
			parse_tree.c \
			parse_tree_utils.c \
			tokenization1.c \
			tokenization2.c \
			display_parse_tree.c \
			ambiguous_redirections.c \
			args_files_separation.c \
			utils_without_garbage_collection.c \
			queue_utils.c \
			here_doc.c \
			init.c \
			signals.c

OBJS =		${SRCS:.c=.o}

NAME =	minishell
CC = cc 
CFLAGS = -Wall -Wextra -Werror
CFLAGS += -fsanitize=address -g
CFLAGS += -I/Users/obednaou/brew/opt/readline/include/
RDLIB = -lreadline -L/Users/obednaou/brew/opt/readline/lib/
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