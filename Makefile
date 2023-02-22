
SRCS=		main.c \
			env_utils.c \
			garbage_collector.c \
			tokenization1.c \
			tokenization2.c \
			check_syntax.c \
			expanding.c \
			removing_quotes.c \
			production_rules1.c \
			production_rules2.c \
			production_rules3.c \
			items_classification.c \
			items_classification_utils1.c \
			items_classification_utils2.c \
			items_classification_utils3.c \
			queue_utils.c \
			signals.c

OBJS =		${SRCS:.c=.o}

NAME =	minishell
CC = cc 
CFLAGS = -Wall -Wextra -Werror
CFLAGS += -fsanitize=address
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