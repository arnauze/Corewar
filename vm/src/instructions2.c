/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feedme <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 14:58:37 by feedme            #+#    #+#             */
/*   Updated: 2019/03/04 14:58:52 by feedme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/vm.h"

int		get_ind(int i, unsigned char *arena, int size)
{
	char	*str;
	int		index;
	char	*tmp;
	char	*tmp2;
	int		j;

	j = -1;
	str = ft_strnew(0);
	while (++j < size)
	{
		tmp = char_to_bit(arena[(i + j) % MEM_SIZE]);
		tmp2 = ft_strjoin(str, tmp);
		free(str);
		free(tmp);
		str = ft_strdup(tmp2);
		free(tmp2);
	}
	index = bit_to_dec(str, size);
	free(str);
	return (index);
}

int		get_regis(unsigned char *arena, int i)
{
	if ((int)arena[i] < 0)
		return (REG_NUMBER - ((((int)arena[i]) * -1) % REG_NUMBER));
	else if ((int)arena[i] == 0)
		return (REG_NUMBER);
	return ((int)arena[i]);
}

void	fill_regis(unsigned char *reg, char *bits)
{
	int		i;
	int		j;

	i = 24;
	j = 3;
	while (i > -1)
	{
		reg[j] = (unsigned char)bit_to_dec(bits + i, 1);
		i -= 8;
		j--;
	}
}

char	*get_dir(int i, unsigned char *arena)
{
	char	*new;
	int		j;

	j = -1;
	if (!(new = ft_strnew(DIR_SIZE + 1)))
		exit(-1);
	new[DIR_SIZE] = '\0';
	while (++j < DIR_SIZE)
		new[j] = arena[(i + j) % MEM_SIZE];
	return (new);
}

char	*cw_strsub(unsigned char *arena, int i, int size)
{
	char	*new;
	int		j;

	j = -1;
	if (!(new = ft_strnew(size + 1)))
		exit(-1);
	new[size] = '\0';
	while (++j < size)
		new[j] = arena[(i + j) % MEM_SIZE];
	return (new);
}
