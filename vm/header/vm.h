/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 23:10:01 by amagnan           #+#    #+#             */
/*   Updated: 2018/12/10 23:10:02 by amagnan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "../../libft/libft.h"
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
	int				op_code;
	int				coding_byte;
	int				args_t[3];
	int				args[3];
	int				size;
}					t_action;

typedef struct 		s_player
{
	header_t		header;
	t_action		actions;
	t_action		memory;
	int				c_to_wait;
	char			r[REG_NUMBER + 1][REG_SIZE + 1];
}					t_player;

#endif
