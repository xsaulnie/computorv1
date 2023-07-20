SRCS	:=	main.cpp		\

SRCB := main_bonus.cpp

OBJS	=	${SRCS:.cpp=.o}

OBJB	=	${SRCB:.cpp=.o}

DEP		=	${SRCS:.cpp=.d}

DEPB	= 	${SRCB:.cpp=.d}

FLAGS	:=	-Wall -Wextra -Werror -g #-std=c++98

NAME	:=	computor

.SUFFIXES: .cpp .o .d

.cpp.d:
		c++ -MM $< -MF ${<:.cpp=.d}

.cpp.o:
		c++ ${FLAGS} -c $< -o ${<:.cpp=.o}

all:	dependencies ${NAME}

clean:
		rm -f ${OBJS}
		rm -r ${OBJB}
		rm -f ${DEP}
		rm -f ${DEPB}

fclean:		clean
		rm -f ${NAME}

${NAME}: ${OBJS}
		c++ ${FLAGS} -o ${NAME} ${OBJS}

bonus: dependenciesb ${OBJB}
	c++ ${FLAGS} -o ${NAME} ${OBJB}

dependencies:
include ${DEP}

dependenciesb:
include ${DEPB}

re:		fclean all

.PHONY:		all clean fclean re dependencies