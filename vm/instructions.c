/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feedme <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 17:46:50 by feedme            #+#    #+#             */
/*   Updated: 2018/12/12 01:20:23 by feedme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

int		load(t_player *pl, unsigned char *arena)
{
	char	*tmp;
	int		i;

	if (get_type(pl, arena))
		tmp = get_dir(pl, arena);
	else
		tmp = get_ind(pl, arena);
	i = get_index(pl, arena) - 1;
	pl->regs[i] = ft_strncpy(pl->reg[i], tmp, REG_SIZE);
	return (get_len(pl, arena));
}
