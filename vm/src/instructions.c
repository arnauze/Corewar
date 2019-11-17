/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feedme <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 17:46:50 by feedme            #+#    #+#             */
/*   Updated: 2019/03/07 16:20:23 by feedme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/vm.h"

char	*char_to_bit(unsigned char c)
{
	char	*bitstr;
	int		i;

	if (!(bitstr = ft_strnew(9)))
		ft_exit_msg("Malloc error \n");
	bitstr[8] = '\0';
	i = 8;
	while (c > 0)
	{
		bitstr[--i] = (c % 2) ? '1' : '0';
		c /= 2;
	}
	while (--i >= 0)
		bitstr[i] = '0';
	return (bitstr);
}

char	*int_to_bit(int c)
{
	char	*bitstr;
	int		i;

	if (!(bitstr = ft_strnew(33)))
		ft_exit_msg("Malloc error \n");
	bitstr[32] = '\0';
	i = 32;
	while (c > 0)
	{
		bitstr[--i] = (c % 2) ? '1' : '0';
		c /= 2;
	}
	while (--i >= 0)
		bitstr[i] = '0';
	return (bitstr);
}

int		ft_powof2(int pow)
{
	int		res;

	res = 1;
	while (--pow > -1)
		res *= 2;
	return (res);
}

int		bit_to_dec(char *str, int size)
{
	int		i;
	int		res;
	int		pow;

	pow = 0;
	res = 0;
	i = 8 * size;
	while (--i >= 0)
	{
		res += (str[i] - '0') * ft_powof2(pow);
		pow++;
	}
	return (res);
}

void	set_last_alive(t_vm *vm, char *tmp)
{
	if (!ft_memcmp(vm->p1->nbr, tmp, DIR_SIZE))
	{
		vm->p1->last_live = 1;
		vm->p2->last_live = 0;
	}
	else if (!ft_memcmp(vm->p2->nbr, tmp, DIR_SIZE))
	{
		vm->p1->last_live = 0;
		vm->p2->last_live = 1;
	}
}
