/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_validity_instructions.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 13:34:26 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/03/13 18:17:30 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
**	BEWARE: the functions below return the ins_code (between 1 and 16) \
**	in case of invalidity and 100 if the instruction is valid!
*/

int		check_valid_ins_sub(t_ins *ins)
{
	if (ins->ins_code == 5 && (check_valid_param(ins->par1, 1, 0, 0) == 0
							|| check_valid_param(ins->par2, 1, 0, 0) == 0
							|| check_valid_param(ins->par3, 1, 0, 0) == 0))
		return (ins->ins_code);
	if (ins->ins_code == 6 && (check_valid_param(ins->par1, 1, 1, 1) == 0
							|| check_valid_param(ins->par2, 1, 1, 1) == 0
							|| check_valid_param(ins->par3, 1, 0, 0) == 0))
		return (ins->ins_code);
	if (ins->ins_code == 7 && (check_valid_param(ins->par1, 1, 1, 1) == 0
							|| check_valid_param(ins->par2, 1, 1, 1) == 0
							|| check_valid_param(ins->par3, 1, 0, 0) == 0))
		return (ins->ins_code);
	if (ins->ins_code == 8 && (check_valid_param(ins->par1, 1, 1, 1) == 0
							|| check_valid_param(ins->par2, 1, 1, 1) == 0
							|| check_valid_param(ins->par3, 1, 0, 0) == 0))
		return (ins->ins_code);
	if (ins->ins_code == 9 && (check_valid_param(ins->par1, 0, 1, 0) == 0
							|| check_valid_param(ins->par2, 0, 0, 0) == 0
							|| check_valid_param(ins->par3, 0, 0, 0) == 0))
		return (ins->ins_code);
	if (ins->ins_code == 10 && (check_valid_param(ins->par1, 1, 1, 1) == 0
							|| check_valid_param(ins->par2, 1, 1, 0) == 0
							|| check_valid_param(ins->par3, 1, 0, 0) == 0))
		return (ins->ins_code);
	return (100);
}

int		check_valid_ins_sub2(t_ins *ins)
{
	if (ins->ins_code == 11 && (check_valid_param(ins->par1, 1, 0, 0) == 0
							|| check_valid_param(ins->par2, 1, 1, 1) == 0
							|| check_valid_param(ins->par3, 1, 1, 0) == 0))
		return (ins->ins_code);
	if (ins->ins_code == 12 && (check_valid_param(ins->par1, 0, 1, 0) == 0
							|| check_valid_param(ins->par2, 0, 0, 0) == 0
							|| check_valid_param(ins->par3, 0, 0, 0) == 0))
		return (ins->ins_code);
	if (ins->ins_code == 13 && (check_valid_param(ins->par1, 0, 1, 1) == 0
							|| check_valid_param(ins->par2, 1, 0, 0) == 0
							|| check_valid_param(ins->par3, 0, 0, 0) == 0))
		return (ins->ins_code);
	if (ins->ins_code == 14 && (check_valid_param(ins->par1, 1, 1, 1) == 0
							|| check_valid_param(ins->par2, 1, 1, 0) == 0
							|| check_valid_param(ins->par3, 1, 0, 0) == 0))
		return (ins->ins_code);
	if (ins->ins_code == 15 && (check_valid_param(ins->par1, 0, 1, 0) == 0
							|| check_valid_param(ins->par2, 0, 0, 0) == 0
							|| check_valid_param(ins->par3, 0, 0, 0) == 0))
		return (ins->ins_code);
	if (ins->ins_code == 16 && (check_valid_param(ins->par1, 1, 0, 0) == 0
							|| check_valid_param(ins->par2, 0, 0, 0) == 0
							|| check_valid_param(ins->par3, 0, 0, 0) == 0))
		return (ins->ins_code);
	return (100);
}

int		check_valid_ins_sub3(t_ins *ins)
{
	if (ins->ins_code == 17 && (check_valid_param(ins->par1, 1, 0, 0) == 0
							|| check_valid_param(ins->par2, 1, 0, 0) == 0
							|| check_valid_param(ins->par3, 0, 0, 0) == 0))
		return (ins->ins_code);
	if (ins->ins_code == 18 && (check_valid_param(ins->par1, 0, 0, 0) == 0
							|| check_valid_param(ins->par2, 0, 0, 0) == 0
							|| check_valid_param(ins->par3, 0, 0, 0) == 0))
		return (ins->ins_code);
	return (100);
}

int		check_valid_ins(t_ins *ins, int val, int val2, int val3)
{
	if (ins->ins_code == 1 && (check_valid_param(ins->par1, 0, 1, 0) == 0
							|| check_valid_param(ins->par2, 0, 0, 0) == 0
							|| check_valid_param(ins->par3, 0, 0, 0) == 0))
		return (ins->ins_code);
	if (ins->ins_code == 2 && (check_valid_param(ins->par1, 0, 1, 1) == 0
							|| check_valid_param(ins->par2, 1, 0, 0) == 0
							|| check_valid_param(ins->par3, 0, 0, 0) == 0))
		return (ins->ins_code);
	if (ins->ins_code == 3 && (check_valid_param(ins->par1, 1, 0, 0) == 0
							|| check_valid_param(ins->par2, 1, 0, 1) == 0
							|| check_valid_param(ins->par3, 0, 0, 0) == 0))
		return (ins->ins_code);
	if (ins->ins_code == 4 && (check_valid_param(ins->par1, 1, 0, 0) == 0
							|| check_valid_param(ins->par2, 1, 0, 0) == 0
							|| check_valid_param(ins->par3, 1, 0, 0) == 0))
		return (ins->ins_code);
	if ((val = check_valid_ins_sub(ins)) != 100
		|| (val2 = check_valid_ins_sub2(ins)) != 100
		|| (val3 = check_valid_ins_sub3(ins)) != 100)
		return (ft_min(val, val2, val3));
	return (100);
}

/*
**	In this function, we go down the instruction and we check if \
**	the parameters for an instruction are coherent with the instruction \
**	number (all instructions don't accept the same parameter number \
**	and the same parameters type (register vs direct and indirect params)).
**	The check ins->ins_code != 0 is to not consider the node that \
**	have no instruction, i.e. that just contain a label.
*/

void	check_validity_instructions(t_champ *champ)
{
	t_ins	*ins;
	int		ins_code;

	ins = champ->ins;
	if (!ins)
	{
		ft_syntax_error("there is no instruction (or label)", champ);
	}
	while (ins)
	{
		if (ins->ins_code != 0
			&& (ins_code = check_valid_ins(ins, 100, 100, 100)) != 100)
		{
			ft_putstr_fd("invalid instruction type:", 2);
			ft_putstr_fd(g_op_tab[ins_code - 1].name, 2);
			ft_syntax_error("there is an invalid instruction", champ);
		}
		ins = ins->next;
	}
	(void)ins_code;
}
