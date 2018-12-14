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
# include "../../terminal/term.h"
# include "../../op/op.h"

typedef struct		header_s
{
  unsigned int		magic;
  char				prog_name[PROG_NAME_LENGTH + 1];
  unsigned int		prog_size;
  char				comment[COMMENT_LENGTH + 1];
}					header_t;

typedef struct 		s_action
{
	int				max;
	int				track;
	int				*size;
}					t_action;

typedef struct 		s_player
{
	header_t		header;
	t_action		action;
	char			memory[16];
	int				c_to_wait;
	char			r[REG_NUMBER + 1][REG_SIZE + 1];
	int				fd;
	unsigned int	index;
}					t_player;

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

typedef struct 		s_vm
{
	t_player		p1;
	t_player		p2;
	t_term			term;
	unsigned char	*arena;
	int				cycle_to_die;
	int				cycle;
	int				checks;
	int				decrease;
	int				live;
}					t_vm;

t_op    			op_tab[17];

#endif
