NAME = minishell
SRCS = ./main.c ./garbage_collector.c ./utils.c
LIBSRCS = ${wildcard libft/*.c}
OBJS = ${SRCS:.c=.o}
LIBOBJS = ${LIBSRCS:.c=.o}
CFLAGS = -Wall -Wextra -Werror

all: ${NAME}

${NAME}: ${OBJS} ${LIBOBJS}
	gcc ${CFLAGS} ${OBJS} ${LIBOBJS} -o ${NAME}

clean:
	rm -rf ${OBJS} ${LIBOBJS}

fclean: clean
	rm -rf ${NAME}

re: fclean all