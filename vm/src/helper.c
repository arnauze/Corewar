/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feedme <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 15:38:37 by feedme            #+#    #+#             */
/*   Updated: 2019/03/12 03:14:10 by feedme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/vm.h"

int				get_arg2i_pos(unsigned char code)
{
	if ((code & 192) == 64)
		return (3);
	else if ((code & 192) == 128)
		return (4);
	else if ((code & 192) == 192)
		return (4);
	else
		return (-1);
}

void			lfork(t_process *pl, unsigned char *arena)
{
	int		index;
	int		new_i;

	index = get_ind((pl->index + 1) % MEM_SIZE, arena, IND_SIZE);
	new_i = (pl->index + index) % MEM_SIZE;
	add_node(new_i, pl, pl);
	pl->carry = (pl->carry) ? 0 : 1;
}

void			free_all2(t_vm *vm)
{
	if (vm->p1)
	{
		if (vm->p1->nbr)
			free(vm->p1->nbr);
		free(vm->p1);
	}
	if (vm->p2)
	{
		if (vm->p2->nbr)
			free(vm->p2->nbr);
		free(vm->p2);
	}
	if (vm->arena)
		free(vm->arena);
}

void			free_all(t_vm *vm)
{
	t_process	*tmp;
	int			i;

	i = -1;
	if (vm)
	{
		free_all2(vm);
		while (vm->process)
		{
			tmp = vm->process;
			vm->process = vm->process->next;
			if (tmp->r)
			{
				while (++i < REG_NUMBER)
				{
					if (tmp->r[i])
						free(tmp->r[i]);
				}
				free(tmp->r);
			}
			free(tmp);
		}
	}
}

void			initialize_players(t_player *p1, t_player *p2)
{
	p1->last_live = 0;
	p1->nlive = 0;
	p1->talk = 0;
	p1->fd = 0;
	p1->nbr = NULL;
	p2->last_live = 0;
	p2->nlive = 0;
	p2->talk = 0;
	p2->fd = 0;
	p2->nbr = NULL;
}
