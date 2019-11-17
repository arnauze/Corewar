# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/07 13:37:45 by ghdesfos          #+#    #+#              #
#    Updated: 2019/03/13 22:44:16 by ghdesfos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = 	add_ins_to_node.c\
		get_instructions_list.c\
		get_name_and_comment_champion.c\
		get_next_line.c\
		main.c\
		op.c\
		useful_functions.c\
		useful_functions_2.c\
		useful_functions_3.c\
		useful_functions_4.c\
		useful_functions_5.c\
		compute_ins_length.c\
		compute_ins_distance_label.c\
		create_output_file.c\
		add_champion_code_to_output_file.c\
		add_champion_length_to_output_file.c\
		add_ins_parameters_to_champion_code.c\
		check_input.c\
		check_input_2.c\
		check_validity_instructions.c\
		check_validity_instructions_2.c
OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror
NAME = asm
HEAD = -I.

all: $(NAME)

$(NAME):
	gcc $(CFLAGS) $(SRC) -o $(NAME)

g:
	gcc $(CFLAGS) $(SRC) -o $(NAME) -fsanitize=undefined -fsanitize=address

lldb:
	gcc $(CFLAGS) $(SRC) -o $(NAME) -g

clean:
	rm -f $(NAME)

fclean: clean
	rm -f $(OBJ)
	rm -rf *.dSYM

re: fclean all
