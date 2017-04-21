NAME		=	plazza

CC		=	g++

RM		=	rm -rf

SRC		=	./src

CPPFLAGS	+=	-std=c++14 -W -Wall -Wextra -g3

LDFLAGS		= 	-lpthread

SRCS		=	$(SRC)/main.cpp 		\
			$(SRC)/Plazza.cpp 		\
			$(SRC)/PlazzaException.cpp	\
			$(SRC)/OrderParser.cpp		\
			$(SRC)/Process.cpp		\
			$(SRC)/ThreadPool.cpp		\

OBJS		=	$(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
