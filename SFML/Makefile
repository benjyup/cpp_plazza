NAME	= test

CC	= g++

RM	= rm -f

SRCS	= main.cpp \
	Gui.cpp \
	Button.cpp

OBJS	= $(SRCS:.cpp=.o)

CPPFLAGS += -W -Wall -Werror -Wextra -I./

LDFLAGS  = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
