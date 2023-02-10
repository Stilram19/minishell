NAME = minishell
LIBFT = libft.a
LIBSRCS = $(wildcard libft/*.c)
SRCS = garbage_collector.c main.c utils.c
LIBOBJS = ${LIBSRCS:.c=.o}
OBJS = ${SRCS:.c=.o}
CFLAGS = -Wall -Wextra -Werror

all: ${NAME}

${NAME}: ${LIBFT} ${OBJS}
	gcc ${CFLAGS} ${OBJS} -lft -Llibft -o ${NAME}

${LIBFT}: ${LIBOBJS}
	ar rc ${LIBFT} ${LIBSRCS}

clean:
	rm -rf ${OBJS} ${LIBOBJS}

fclean:	clean
	rm -rf ${NAME} ${LIBFT}

re: fclean all