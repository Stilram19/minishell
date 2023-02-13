NAME = test
SRCS = ${wildcard ../libft/*.c} ${wildcard build-ins/*.c} \
				./utils.c ./ft_execvp.c ./execute.c \
				./buildsin_check.c ../utils.c ../garbage_collector.c \
				./here_doc.c
OBJS = ${SRCS:.c=.o}
CFLAGS = -I../
all: ${NAME}

${NAME}: ${OBJS}
	gcc ${OBJS} ${CFLAGS} -lreadline -fsanitize=address -o ${NAME}

clean:
	rm -rf ${OBJS}

fclean: clean
	rm -rf ${NAME}