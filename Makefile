CC		= gcc -g

CFLAGS		= -Wall -Werror -Wextra

NAME		= minishell

INC		= ./inc/

LIB_NAME	= libft/libft.a

SRCS		= $(wildcard ./srcs/*.c ./srcs/*/*.c)

OBJS		= ${SRCS:.c=.o}

RM		= rm -f

.c.o:
		${CC} -I${INC} -c $< -o ${<:.c=.o} -lreadline

$(NAME):	${OBJS}
		make -C libft
		${CC} ${OBJS} ${LIB_NAME} -o ${NAME} -lreadline

all:		${NAME}

clean:
		${RM} ${OBJS}
		make clean -C libft

fclean:		clean
		${RM} ${NAME} ${LIB_NAME}

re:		fclean all

.PHONY:		all clean fclean re
