/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sixteen_to_twenty.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feedme <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 12:02:14 by feedme            #+#    #+#             */
/*   Updated: 2019/03/13 23:16:26 by feedme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/vm.h"

void	swap(t_process *pl, unsigned char *arena)
{
	unsigned char	*tmp;
	int				r1;
	int				r2;

	if (!(tmp = (unsigned char*)malloc(REG_SIZE)))
		ft_exit_msg("malloc failed\n");
	r1 = (get_regis(arena, (pl->index + 1) % MEM_SIZE) - 1) % REG_NUMBER;
	r2 = (get_regis(arena, (pl->index + 2) % MEM_SIZE) - 1) % REG_NUMBER;
	tmp = ft_memcpy(tmp, pl->r[r1], REG_SIZE);
	pl->r[r1] = ft_memcpy(pl->r[r1], pl->r[r2], REG_SIZE);
	pl->r[r2] = ft_memcpy(pl->r[r2], tmp, REG_SIZE);
	free(tmp);
}

void	wipe(t_process *pl, unsigned char *arena)
{
	int	i;

	(void)pl;
	i = -1;
	while (++i < MEM_SIZE)
		arena[i] = 0;
}
