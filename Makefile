NAME	= 	philo

HEADER	= 	philo.h

SRCS	= 	philo.c parse.c init.c action.c utils.c

FLAGS	=	-Wall -Wextra -Werror

OBJS	= 	${SRCS:.c=.o}


all:		${NAME}

%.o:%.c		${HEADER}
			gcc ${FLAGS} -I ${HEADER} -c $< -o $@

${NAME}:	${OBJS} ${HEADER}
			gcc ${FLAGS} ${OBJS} -o $@

clean:
			rm -f ${OBJS}

fclean:		clean
			rm -f ${NAME}
	
re:			fclean all

.PHONY:		all clean fclean re