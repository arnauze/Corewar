/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful_functions_5.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 13:42:13 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/03/13 17:44:10 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	print_t_champ(t_champ *champ)
{
	t_ins	*ins;
	int		i;

	ft_putstr_fd(champ->name, 1);
	ft_putstr_fd(champ->comment, 1);
	ins = champ->ins;
	i = 1;
	while (ins)
	{
		ft_putnbr_fd(i, 1);
		ft_putchar_fd('\n', 1);
		ft_putstr_fd(ins->label, 1);
		ft_putnbr_fd(ins->ins_code, 1);
		ft_putchar_fd('\n', 1);
		ft_putstr_fd(ins->par1, 1);
		ft_putstr_fd(ins->par2, 1);
		ft_putstr_fd(ins->par3, 1);
		ft_putnbr_fd(ins->length, 1);
		ft_putchar_fd('\n', 1);
		ft_putnbr_fd(ins->n, 1);
		ft_putchar_fd('\n', 1);
		ft_putchar_fd('\n', 1);
		i++;
		ins = ins->next;
	}
}

void	initialize_champ_list(t_champ *champ)
{
	champ->name = NULL;
	champ->comment = NULL;
	champ->ins = NULL;
	champ->strtofree = NULL;
}

int		ft_min(int a, int b, int c)
{
	int min;

	min = a;
	if (b < min)
		min = b;
	if (c < min)
		min = c;
	return (min);
}
