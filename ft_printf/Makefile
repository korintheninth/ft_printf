NAME = libftprintf.a
CC = gcc
FLAGS = -Wall -Werror -Wextra
SRCS = ft_printf.c put.c helper_funcs.c libft/ft_isalpha.c libft/ft_isalnum.c
OBJS = ${SRCS:.c=.o}

all: ${NAME}

${NAME}: ${OBJS}
	ar -rcs ${NAME} ${OBJS}

bonus: ${NAME}
	ar -rcs ${NAME} ${OBJS}

clean:
	rm -rf ${OBJS}

fclean: clean
	rm -rf ${NAME}

re: fclean all

.PHONY: all clean fclean re
