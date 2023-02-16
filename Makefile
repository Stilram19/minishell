LIBFT_SRCS= $(wildcard ./libft/*.c)
SRCS=		main.c \
			env_utils.c \
			garbage_collector.c \
			tokenization1.c \
			tokenization2.c \
			check_syntax.c \
			expanding.c \
			removing_quotes.c \
			production_rules.c

OBJS=		${SRCS:.c=.o}
LIBFT_OBJS=	${LIBFT_SRCS:.c=.o}

NAME=	minishell
CC= cc 
CFLAGS= -Wall -Wextra -Werror
RM= rm -f

all: ${NAME}

${NAME}: ${LIBFT_OBJS} ${OBJS}
	${CC} ${CFLAGS} -lreadline ${OBJS} ${LIBFT_OBJS} -o ${NAME}

clean:
	${RM} ${LIBFT_OBJS} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all