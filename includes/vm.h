/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feedme <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 15:56:07 by feedme            #+#    #+#             */
/*   Updated: 2018/12/12 01:20:26 by feedme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "op.h"

//on fait une queue de players et on la cree ds le bon ordre en fonction de l'ordre de commencement

typedef struct		s_player;
{
	int				lifec;
	int				i;
	unsigned char	**regs;
	char			carry;
	struct s_player	*next;
}				t_player;

#endif
