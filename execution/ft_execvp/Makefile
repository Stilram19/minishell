NAME = execvp
SRCS = ./ft_split.c ./ft_execvp.c ./ft_execvp_utils.c
OBJS = ${SRCS:.c=.o}
CFLAGS = -Wall -Wextra -Werror

all: ${NAME}

${NAME}: ${OBJS}
	ar rc ${NAME} ${OBJS}

clean:
	rm -rf ${OBJS}

fclean: clean
	rm -rf ${NAME}

re:	fclean all