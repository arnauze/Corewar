OBJECTS = *.o
SRC = ../op/op.c\
		src/main.c\

LIB = ../libft/libft.a
FLAGS = -Wall -Wextra -Werror
NAME = vm

all: $(NAME)

$(NAME):
	gcc $(FLAGS) $(SRC) -o $(NAME) $(LIB)

sanitize:
	gcc $(FLAGS) $(SRC) -o $(NAME) -fsanitize=address -g $(LIB)

lldb:
	gcc $(FLAGS) -g $(SRC) -o $(NAME) $(LIB)

cleanlldb:
	rm $(NAME)
	rm -rf $(NAME).dSYM

runlldb:
	lldb ./$(NAME)

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all
 
