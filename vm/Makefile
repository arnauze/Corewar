OBJECTS = *.o
SRC = op/op.c\
		src/main.c\
		src/arena.c\
		src/ft_get_player.c\
		src/ft_read_file.c\
		src/process.c\
		src/vm.c\
		src/one_to_five.c\
		src/instructions.c\
		src/instructions2.c\
		src/instructions3.c\
		src/helper.c\
		src/six_to_ten.c\
		src/eleven_to_fifteen.c\
		src/sixteen_to_twenty.c\
		src/helper2.c\
		src/cycles.c\
		src/vm2.c

LIB = ../libft/libft.a\

FLAGS = -Wall -Wextra -Werror -lncurses
NAME = corewar

all: $(NAME)

$(NAME):
	gcc $(FLAGS) $(SRC) -o $(NAME) $(LIB)

sanitize:
	gcc $(FLAGS) $(SRC) -o $(NAME) -g $(LIB)

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
 
test:
	./$(NAME) ../zork.cor ../vm_champs/champs/Gagnant.cor
