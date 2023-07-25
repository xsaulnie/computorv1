SRCS	:= syntax.cpp parcing.cpp solver.cpp main.cpp \

SRCB	:= utils.cpp fract.cpp syntax.cpp parcing.cpp solver.cpp main_bonus.cpp \

OBJS	=	$(addprefix mandatory/, ${SRCS:.cpp=.o})

OBJB	=	$(addprefix bonus/, ${SRCB:.cpp=.o})

DEP		=	$(addprefix mandatory/, ${SRCS:.cpp=.d})

DEPB	= 	$(addprefix bonus/, ${SRCB:.cpp=.d})

FLAGS	:=	-g -fsanitize=address -Wall -Wextra -Werror #-std=c++98 -g

NAME	:=	computor

.SUFFIXES: .cpp .o .d

.cpp.d:
		c++ -MM $< -MF ${<:.cpp=.d}

.cpp.o:
		c++ ${FLAGS} -c $< -o ${<:.cpp=.o}

all:	dependencies ${NAME}

clean:
		rm -rf ${OBJS}
		rm -rf ${OBJB}
		rm -rf ${DEP}
		rm -rf ${DEPB}

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