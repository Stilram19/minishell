NAME = test
SRCS = ${wildcard ../libft/*.c} ${wildcard build-ins/*.c} \
				./ft_execvp.c ./execute.c ./utils.c ./b_tree.c \
				./buildsin_check.c ../utils.c ../garbage_collector.c \

OBJS = ${SRCS:.c=.o}
CFLAGS = -I../
all: ${NAME}

${NAME}: ${OBJS}
	gcc ${OBJS} ${CFLAGS} -lreadline -fsanitize=address -g -o ${NAME}

clean:
	rm -rf ${OBJS}

fclean: clean
	rm -rf ${NAME}