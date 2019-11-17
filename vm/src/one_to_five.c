/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_to_five.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feedme <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 16:44:46 by feedme            #+#    #+#             */
/*   Updated: 2019/03/12 03:15:45 by feedme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/vm.h"
#include <fcntl.h>

void	live(t_process *pl, unsigned char *arena, t_vm *vm)
{
	char	*tmp;

	vm->nlive++;
	pl->nlive++;
	tmp = get_dir(pl->index + 1, arena);
	if (!ft_memcmp(pl->r[0], tmp, DIR_SIZE))
		set_last_alive(vm, tmp);
	free(tmp);
}

void	load(t_process *pl, unsigned char *arena)
{
	char	*tmp;
	int		reg_i;
	char	*code;
	int		ind;

	tmp = NULL;
	code = char_to_bit(arena[(pl->index + 1) % MEM_SIZE]);
	if (code[1] == '0')
		tmp = get_dir((pl->index + 2) % MEM_SIZE, arena);
	else
	{
		ind = get_ind((pl->index + 2) % MEM_SIZE, arena, IND_SIZE);
		tmp = cw_strsub(arena, (pl->index + (ind % IDX_MOD))
		% MEM_SIZE, REG_SIZE);
	}
	reg_i = (code[1] == '0') ? (get_regis(arena,
	(pl->index + 2 + DIR_SIZE) % MEM_SIZE) - 1) % REG_NUMBER :
	(get_regis(arena, (pl->index + 2 + IND_SIZE) % MEM_SIZE) - 1) % REG_NUMBER;
	ft_memcpy(pl->r[reg_i], tmp, REG_SIZE);
	free(tmp);
	free(code);
	pl->carry = (pl->carry) ? 0 : 1;
}

void	store(t_process *pl, unsigned char *arena)
{
	int		reg_i;
	int		i2;
	char	*code;
	int		count;

	reg_i = (get_regis(arena, (pl->index + 2) % MEM_SIZE) - 1) % REG_NUMBER;
	code = char_to_bit(arena[(pl->index + 1) % MEM_SIZE]);
	if (code[2] == '0')
	{
		i2 = (get_regis(arena, (pl->index + 3) % MEM_SIZE) - 1) % REG_NUMBER;
		ft_memcpy(pl->r[i2], pl->r[reg_i], REG_SIZE);
	}
	else
	{
		count = -1;
		i2 = pl->index + (get_ind((pl->index + 3) % MEM_SIZE,
		arena, IND_SIZE) % IDX_MOD);
		while (++count < REG_SIZE)
			arena[(i2 + count) % MEM_SIZE] = pl->r[reg_i][count];
	}
	free(code);
}

void	add(t_process *pl, unsigned char *arena)
{
	int		res;
	int		nb1;
	int		nb2;
	char	*tmp;

	nb1 = get_ind(0, pl->r[(get_regis(arena, (pl->index + 2) %
	MEM_SIZE) - 1) % REG_NUMBER], REG_SIZE);
	nb2 = get_ind(0, pl->r[(get_regis(arena, (pl->index + 3) %
	MEM_SIZE) - 1) % REG_NUMBER], REG_SIZE);
	res = (nb1 + nb2) % MEM_SIZE;
	tmp = int_to_bit(res);
	fill_regis(pl->r[(get_regis(arena, (pl->index + 4) % MEM_SIZE)
	- 1) % REG_NUMBER], tmp);
	free(tmp);
	pl->carry = (pl->carry) ? 0 : 1;
}

void	sub(t_process *pl, unsigned char *arena)
{
	int		res;
	int		nb1;
	int		nb2;
	char	*tmp;

	nb1 = get_ind(0, pl->r[(get_regis(arena, (pl->index + 2)
	% MEM_SIZE) - 1) % REG_NUMBER], REG_SIZE);
	nb2 = get_ind(0, pl->r[(get_regis(arena, (pl->index + 3)
	% MEM_SIZE) - 1) % REG_NUMBER], REG_SIZE);
	res = (nb1 - nb2) % MEM_SIZE;
	tmp = int_to_bit(res);
	fill_regis(pl->r[(get_regis(arena, (pl->index + 4) % MEM_SIZE)
	- 1) % REG_NUMBER], tmp);
	free(tmp);
	pl->carry = (pl->carry) ? 0 : 1;
}
