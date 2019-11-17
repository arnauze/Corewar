/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   six_to_ten.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feedme <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 14:53:36 by feedme            #+#    #+#             */
/*   Updated: 2019/03/07 16:23:20 by feedme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/vm.h"

void	and(t_process *pl, unsigned char *arena)
{
	int		res;
	int		nb1;
	int		nb2;
	char	*tmp;

	nb1 = get_nb(((pl->index + 2) % MEM_SIZE), arena, arena[(pl->index + 1)
	% MEM_SIZE] & 192, pl);
	nb2 = get_nb((pl->index + get_arg2_pos(arena[(pl->index + 1) % MEM_SIZE]))
	% MEM_SIZE, arena, arena[(pl->index + 1) % MEM_SIZE] & 48, pl);
	res = (nb1 & nb2) % MEM_SIZE;
	tmp = int_to_bit(res);
	fill_regis(pl->r[(get_regis(arena, (pl->index +
	get_arg3_pos(arena[(pl->index + 1) % MEM_SIZE])) % MEM_SIZE) - 1) %
	REG_NUMBER], tmp);
	free(tmp);
	pl->carry = (pl->carry) ? 0 : 1;
}

void	or(t_process *pl, unsigned char *arena)
{
	int		res;
	int		nb1;
	int		nb2;
	char	*tmp;

	nb1 = get_nb(((pl->index + 2) % MEM_SIZE), arena, arena[(pl->index + 1)
	% MEM_SIZE] & 192, pl);
	nb2 = get_nb((pl->index + get_arg2_pos(arena[(pl->index + 1) % MEM_SIZE]))
	% MEM_SIZE, arena, arena[(pl->index + 1) % MEM_SIZE] & 48, pl);
	res = (nb1 | nb2) % MEM_SIZE;
	tmp = int_to_bit(res);
	fill_regis(pl->r[(get_regis(arena, (pl->index +
	get_arg3_pos(arena[(pl->index + 1) % MEM_SIZE])) % MEM_SIZE) - 1) %
	REG_NUMBER], tmp);
	free(tmp);
	pl->carry = (pl->carry) ? 0 : 1;
}

void	xor(t_process *pl, unsigned char *arena)
{
	int		res;
	int		nb1;
	int		nb2;
	char	*tmp;

	nb1 = get_nb(((pl->index + 2) % MEM_SIZE), arena, arena[(pl->index + 1)
	% MEM_SIZE] & 192, pl);
	nb2 = get_nb((pl->index + get_arg2_pos(arena[(pl->index + 1) % MEM_SIZE]))
	% MEM_SIZE, arena, arena[(pl->index + 1) % MEM_SIZE] & 48, pl);
	res = (nb1 ^ nb2) % MEM_SIZE;
	tmp = int_to_bit(res);
	fill_regis(pl->r[(get_regis(arena, (pl->index +
	get_arg3_pos(arena[(pl->index + 1) %
	MEM_SIZE])) % MEM_SIZE) - 1) % REG_NUMBER], tmp);
	free(tmp);
	pl->carry = (pl->carry) ? 0 : 1;
}

void	zjump(t_process *pl, unsigned char *arena)
{
	int	i;

	i = get_ind((pl->index + 1) % MEM_SIZE, arena, IND_SIZE);
	if (pl->carry == 1)
	{
		pl->index += (i % IDX_MOD);
		pl->index %= MEM_SIZE;
	}
}

void	ldi(t_process *pl, unsigned char *arena)
{
	int		index;
	int		i1;
	int		i2;
	int		reg_i;
	char	*tmp;

	pl->flag = 1;
	i1 = get_nb((pl->index + 2) % MEM_SIZE, arena, arena[(pl->index + 1)
	% MEM_SIZE] & 192, pl);
	i2 = get_nb((pl->index + get_arg2i_pos(arena[(pl->index + 1) % MEM_SIZE]))
	% MEM_SIZE, arena, arena[(pl->index + 1) % MEM_SIZE] & 48, pl);
	index = (i1 + i2) % IDX_MOD;
	tmp = cw_strsub(arena, (pl->index + index) % MEM_SIZE, REG_SIZE);
	reg_i = (get_regis(arena, (pl->index + get_arg3i_pos(arena[(pl->index + 1)
	% MEM_SIZE])) % MEM_SIZE) - 1) % REG_NUMBER;
	ft_memcpy(pl->r[reg_i], tmp, REG_SIZE);
	free(tmp);
	pl->carry = (pl->carry) ? 0 : 1;
	pl->flag = 0;
}
