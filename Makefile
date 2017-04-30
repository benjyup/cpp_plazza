NAME		=	plazza

CC		=	g++

RM		=	rm -rf

SRC		=	./src

SFML		=	./SFML

CPPFLAGS	+=	-std=c++14 -W -Wall -Wextra -I./SFML/ -I./src/ -g3

LDFLAGS		= 	-lpthread

SRCS		=	$(SRC)/main.cpp 		\
			$(SRC)/Plazza.cpp 		\
			$(SRC)/PlazzaException.cpp	\
			$(SRC)/OrderParser.cpp		\
			$(SRC)/Process.cpp		\
			$(SRC)/ThreadPool.cpp		\
			$(SRC)/Server.cpp		\
			$(SRC)/Client.cpp		\
			$(SRC)/ParserFile.cpp		\
			$(SRC)/ServerException.cpp	\
			$(SRC)/ClientException.cpp

OBJS		=	$(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

ui:
	make -C $(SFML)
clean:
	$(RM) $(OBJS)
	make clean -C $(SFML)

fclean: clean
	$(RM) $(NAME)
	make fclean -C $(SFML)

re: fclean all

.PHONY: all clean fclean re
