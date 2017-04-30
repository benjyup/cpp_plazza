NAME		=	plazza

CC		=	g++

RM		=	rm -rf

SRC		=	./src

SFML		=	./SFML

CPPFLAGS	+=	-std=c++14 -W -Wall -Wextra -I./SFML/ -I./src/ -g3

LDFLAGS		= 	-lpthread

LDFLAGS2	=	-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lpthread

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

SRCS2	= 		$(SFML)/main.cpp		\
			$(SFML)/Gui.cpp			\
			$(SRC)/Plazza.cpp 		\
			$(SRC)/PlazzaException.cpp	\
			$(SRC)/OrderParser.cpp		\
			$(SRC)/Process.cpp		\
			$(SRC)/ThreadPool.cpp		\
			$(SRC)/Server.cpp		\
			$(SRC)/Client.cpp		\
			$(SRC)/ParserFile.cpp		\
			$(SRC)/ServerException.cpp	\
			$(SRC)/ClientException.cpp	\
			$(SFML)/Button.cpp

OBJS		=	$(SRCS:.cpp=.o)

OBJS2		=	$(SRCS2:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

ui: fclean $(OBJS2)
	$(CC) -o $(NAME) $(OBJS2) $(LDFLAGS2)

clean:
	$(RM) $(OBJS)
	$(RM) $(OBJS2)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
