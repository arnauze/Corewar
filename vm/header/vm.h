/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Arnaud <Arnaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 23:10:01 by amagnan           #+#    #+#             */
/*   Updated: 2018/12/13 16:18:58 by Arnaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "../../libft/libft.h"
// # include "../../terminal/term.h"
# include "../../op/op.h"
# include <ncurses.h>

typedef struct		header_s
{
  unsigned int		magic;
  char				prog_name[PROG_NAME_LENGTH + 1];
  unsigned int		prog_size;
  char				comment[COMMENT_LENGTH + 1];
}					header_t;

typedef struct 		s_process
{
	int				id;
	int				c_to_wait;
	char			r[REG_NUMBER + 1][REG_SIZE + 1];
	int				nlive;
	unsigned int	index;
	int				carry;
	struct s_process	*next;
}					t_process;

typedef struct 		s_player
{
	header_t		header;
	int				talk;
	int				nlive;
	int				fd;
}					t_player;

typedef struct 		s_vm
{
	t_player		p1;
	t_player		p2;
	t_process		*process;
	// t_term			term;
	unsigned char	*arena;
	int				cycle_to_die;
	int				tcycle;
	int				cycle;
	int				checks;
	int				nlive;
	int				last_live;
}					t_vm;

typedef struct 		s_op
{
	char			*command;
	int				nb_arg;
	int				arg_type[3];
	int				op_code;
	int				nb_cycle;
	char			*lcommand;
	char			coding_byte;
	char			size;
}					t_op;

t_op    			op_tab[17];

unsigned char		*ft_read_files(char **argv, t_vm *vm);
int					ft_get_player(t_player *p, unsigned char *arena);
t_process			*make_node(int id);
void				add_node(t_process *head, t_process *copy);
void				delete_node(t_process *head, int id);
void				start_vm(t_vm *vm);
t_vm				get_vm(char **argv, t_vm *new);
void				initialize_process(t_vm *vm);
void				output_arena(t_vm *vm);

#endif
