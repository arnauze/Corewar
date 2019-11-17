/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful_functions_4.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 12:53:47 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/03/08 20:17:04 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		avoid_int_overflow_atoi(long number, int sign)
{
	if (number * (long)sign > 2147483647 || number * (long)sign < -2147483648)
		return (1);
	return (0);
}

int		ft_atoi(char *str)
{
	int		i;
	int		sign;
	long	number;

	i = 0;
	sign = 1;
	number = 0;
	while ((str[i] == ' ') || (str[i] == '\t') || (str[i] == '\n')
		|| (str[i] == '\v') || (str[i] == '\f') || (str[i] == '\r'))
		i++;
	if (str[i] == '-')
		sign = -1;
	if ((str[i] == '-') || (str[i] == '+'))
		i++;
	while ((str[i] >= '0') && (str[i] <= '9'))
	{
		number *= 10;
		number += ((int)str[i] - '0');
		if (avoid_int_overflow_atoi(number, sign) == 1)
			return (-1);
		i++;
	}
	return (sign * number);
}

void	free_ins_node(t_ins *ins)
{
	if (!ins)
		return ;
	if (ins->label)
		free(ins->label);
	if (ins->par1)
		free(ins->par1);
	if (ins->par2)
		free(ins->par2);
	if (ins->par3)
		free(ins->par3);
	free(ins);
}

void	free_champ_node(t_champ *champ)
{
	t_ins *ins;
	t_ins *tmp;

	if (!champ)
		return ;
	if (champ->name)
		free(champ->name);
	if (champ->comment)
		free(champ->comment);
	ins = champ->ins;
	while (ins)
	{
		tmp = ins->next;
		free_ins_node(ins);
		ins = tmp;
	}
	if (champ->strtofree)
		free(champ->strtofree);
}

char	*ft_concat_one_char_and_one_string(char c, char *s2)
{
	char *str1;
	char *str2;

	if (!(str1 = (char*)malloc(sizeof(char) * 2)))
		return (NULL);
	str1[0] = c;
	str1[1] = 0;
	str2 = ft_concat_strings(str1, s2, 3);
	return (str2);
}
