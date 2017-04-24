NAME	= test

CC	= g++

RM	= rm -f

SRCS	= main.cpp \
	Button.cpp

OBJS	= $(SRCS:.cpp=.o)

CPPFLAGS += -W -Wall -Werror -Wextra -I./

LDFLAGS  = -lsfml-graphics -lsfml-window -lsfml-system

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
