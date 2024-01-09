CC = gcc
SRCS = ft_printf.c put.c helper_funcs.c libft/ft_isalpha.c libft/ft_isalnum.c libft/ft_bzero.c libft/ft_isdigit.c hex_len.c
OBJS = ${SRCS:.c=.o}
NAME = libftprintf.a
LIBC = ar rcs
RM = rm -f
CFLAGS = -Wall -Wextra -Werror

all: ${NAME}

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${OBJS}
	${LIBC} ${NAME} ${OBJS}

bonus: ${NAME} ${OBJS}
		${LIBC} ${NAME} ${OBJS}

clean:
	${RM} ${OBJS} ${OBJS}

fclean: clean
	${RM} ${NAME} ${bonus}

re: fclean all

.PHONY : all bonus clean fclean re
