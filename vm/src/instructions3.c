/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feedme <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 14:59:33 by feedme            #+#    #+#             */
/*   Updated: 2019/03/07 16:24:41 by feedme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/vm.h"

int		get_arg3_pos(unsigned char code)
{
	if ((code & 240) == 80)
		return (4);
	else if ((code & 240) == 96 || (code & 240) == 144)
		return (7);
	else if ((code & 240) == 112 || (code & 240) == 208)
		return (5);
	else if ((code & 240) == 160)
		return (10);
	else if ((code & 240) == 176 || (code & 240) == 224)
		return (8);
	else if ((code & 240) == 240)
		return (6);
	else
		return (-1);
}

int		get_arg3i_pos(unsigned char code)
{
	if ((code & 240) == 80)
		return (4);
	else if ((code & 240) == 96 || (code & 240) == 144)
		return (5);
	else if ((code & 240) == 112 || (code & 240) == 208)
		return (5);
	else if ((code & 240) == 160)
		return (6);
	else if ((code & 240) == 176 || (code & 240) == 224)
		return (6);
	else if ((code & 240) == 240)
		return (6);
	else
		return (-1);
}

int		get_nb(int i, unsigned char *arena, unsigned char code, t_process *pl)
{
	int	index;

	if (code == 4 || code == 16 || code == 64)
		return (get_ind(0, pl->r[(get_regis(arena, i) - 1) %
		REG_NUMBER], REG_SIZE));
	else if (code == 8 || code == 32 || code == 128)
	{
		if (pl->flag)
			return (get_ind(i, arena, IND_SIZE));
		else
			return (get_ind(i, arena, DIR_SIZE));
	}
	else
	{
		index = get_ind(i, arena, IND_SIZE);
		return (get_ind((pl->index + (index % IDX_MOD)) % MEM_SIZE,
		arena, IND_SIZE));
	}
}

int		get_lnb(int i, unsigned char *arena, unsigned char code, t_process *pl)
{
	int	index;

	if (code == 4 || code == 16 || code == 64)
		return (get_ind(0, pl->r[(get_regis(arena, i) - 1) %
		REG_NUMBER], REG_SIZE));
	else if (code == 8 || code == 32 || code == 128)
	{
		if (pl->flag)
			return (get_ind(i, arena, IND_SIZE));
		else
			return (get_ind(i, arena, DIR_SIZE));
	}
	else
	{
		index = get_ind(i, arena, IND_SIZE);
		return (get_ind((pl->index + index) % MEM_SIZE, arena, IND_SIZE));
	}
}

int		get_arg2_pos(unsigned char code)
{
	if ((code & 192) == 64)
		return (3);
	else if ((code & 192) == 128)
		return (6);
	else if ((code & 192) == 192)
		return (4);
	else
		return (-1);
}
