/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eleven_to_fifteen.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feedme <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 14:54:57 by feedme            #+#    #+#             */
/*   Updated: 2019/03/07 16:25:05 by feedme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/vm.h"

void	sti(t_process *pl, unsigned char *arena)
{
	int		index;
	int		i1;
	int		i2;
	int		reg_i;
	int		i;

	pl->flag = 1;
	i = -1;
	i1 = get_nb((pl->index + get_arg2i_pos(arena[(pl->index + 1) % MEM_SIZE]))
	% MEM_SIZE, arena, arena[(pl->index + 1) % MEM_SIZE] & 48, pl);
	i2 = get_nb((pl->index + get_arg3i_pos(arena[(pl->index + 1) % MEM_SIZE]))
	% MEM_SIZE, arena, arena[(pl->index + 1) % MEM_SIZE] & 12, pl);
	index = (i1 + i2) % MEM_SIZE;
	reg_i = (get_regis(arena, (pl->index + 2) % MEM_SIZE) - 1) % REG_NUMBER;
	while (++i < 4)
		arena[(i + pl->index + index) % MEM_SIZE] = pl->r[reg_i][i];
	pl->flag = 0;
}

void	forki(t_process *pl, unsigned char *arena)
{
	int		index;
	int		new_i;

	index = get_ind((pl->index + 1) % MEM_SIZE, arena, IND_SIZE);
	new_i = (pl->index + (index % IDX_MOD)) % MEM_SIZE;
	add_node(new_i, pl, pl);
}

void	aff(t_process *pl, unsigned char *arena)
{
	char	*bits;
	int		i;
	int		reg;
	char	*tmp;
	char	*tmp2;

	i = -1;
	if (!(bits = ft_strnew(0)))
		exit(-1);
	reg = (get_regis(arena, (pl->index + 2) % MEM_SIZE) - 1) % REG_NUMBER;
	while (++i < REG_SIZE)
	{
		tmp = char_to_bit(pl->r[reg][i]);
		tmp2 = ft_strjoin(bits, tmp);
		free(bits);
		free(tmp);
		bits = tmp2;
	}
	mvprintw(34, 202, "aff: %c", (bit_to_dec(bits, REG_SIZE) % 256));
	free(bits);
}

void	lld(t_process *pl, unsigned char *arena)
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
		tmp = cw_strsub(arena, (pl->index + ind) % MEM_SIZE, REG_SIZE);
	}
	reg_i = (code[1] == '0') ? (get_regis(arena, (pl->index + 2 + DIR_SIZE)
	% MEM_SIZE) - 1) % REG_NUMBER : (get_regis(arena, (pl->index + 2 + IND_SIZE)
	% MEM_SIZE) - 1) % REG_NUMBER;
	ft_memcpy(pl->r[reg_i], tmp, REG_SIZE);
	free(tmp);
	free(code);
	pl->carry = (pl->carry) ? 0 : 1;
}

void	lldi(t_process *pl, unsigned char *arena)
{
	int		index;
	int		i1;
	int		i2;
	int		reg_i;
	char	*tmp;

	pl->flag = 1;
	i1 = get_lnb((pl->index + 2) % MEM_SIZE, arena, arena[(pl->index + 1)
	% MEM_SIZE] & 192, pl);
	i2 = get_lnb((pl->index + get_arg2i_pos(arena[(pl->index + 1) % MEM_SIZE]))
	% MEM_SIZE, arena, arena[(pl->index + 1) % MEM_SIZE] & 48, pl);
	index = (i1 + i2) % MEM_SIZE;
	tmp = cw_strsub(arena, (pl->index + index) % MEM_SIZE, REG_SIZE);
	reg_i = (get_regis(arena, (pl->index + get_arg3i_pos(arena[(pl->index + 1)
	% MEM_SIZE])) % MEM_SIZE) - 1) % REG_NUMBER;
	ft_memcpy(pl->r[reg_i], tmp, REG_SIZE);
	free(tmp);
	pl->carry = (pl->carry) ? 0 : 1;
	pl->flag = 0;
}
