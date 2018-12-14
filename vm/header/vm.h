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
	t_action		memory;
	int				c_to_wait;
	char			r[REG_NUMBER + 1][REG_SIZE + 1];
	int				fd;
	unsigned int	index;
}					t_player;

#endif
