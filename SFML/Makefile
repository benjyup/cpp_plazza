NAME	= plazza

CC	= g++

CP	= cp

RACINE	= ../

RM	= rm -f

SRC		=	../src

SRCS	= main.cpp \
	Gui.cpp \
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
	Button.cpp

OBJS	= $(SRCS:.cpp=.o)

CPPFLAGS += -W -Wall -Werror -Wextra -I./ -I../src/ -std=c++14

LDFLAGS  = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lpthread

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) $(LDFLAGS)
	 $(CP) $(NAME) $(RACINE)
clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
