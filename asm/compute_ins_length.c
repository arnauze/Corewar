/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_ins_length.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 23:41:35 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/03/13 18:09:32 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		get_size_coding_byte(t_ins *ins)
{
	return ((g_op_tab[ins->ins_code - 1]).coding_byte);
}

int		get_size_register_parameters(t_ins *ins)
{
	int n;

	n = 0;
	if (ins->par1 && (ins->par1)[0] == 'r')
		n++;
	if (ins->par2 && (ins->par2)[0] == 'r')
		n++;
	if (ins->par3 && (ins->par3)[0] == 'r')
		n++;
	return (n);
}

int		get_size_direct_parameters(t_ins *ins)
{
	int n;

	n = 0;
	if (ins->par1 && (ins->par1)[0] == DIRECT_CHAR)
		n += ((g_op_tab[ins->ins_code - 1]).dir_size == 1) ? 2 : 4;
	if (ins->par2 && (ins->par2)[0] == DIRECT_CHAR)
		n += ((g_op_tab[ins->ins_code - 1]).dir_size == 1) ? 2 : 4;
	if (ins->par3 && (ins->par3)[0] == DIRECT_CHAR)
		n += ((g_op_tab[ins->ins_code - 1]).dir_size == 1) ? 2 : 4;
	return (n);
}

int		get_size_indirect_parameters(t_ins *ins)
{
	int n;

	n = 0;
	if (ins->par1
			&& (ins->par1)[0] != DIRECT_CHAR && (ins->par1)[0] != 'r')
		n += 2;
	if (ins->par2
			&& (ins->par2)[0] != DIRECT_CHAR && (ins->par2)[0] != 'r')
		n += 2;
	if (ins->par3
			&& (ins->par3)[0] != DIRECT_CHAR && (ins->par3)[0] != 'r')
		n += 2;
	return (n);
}

/*
**	This function computes for each node inside the ins list \
**	(instruction list) the size of the instruction that it contains.
**	Some nodes may just have a label (no instruction), in this case, the \
**	length corresponding to this node is 0, as there is no instruction in it.
**	We will add then the size of the different parameters of \
**	the instructions based on their type.
*/

void	compute_ins_length(t_champ *champ)
{
	t_ins	*ins;
	int		ins_len;

	ins = champ->ins;
	while (ins)
	{
		ins_len = 0;
		if (ins->ins_code != 0)
			ins_len = 1;
		ins_len += get_size_coding_byte(ins);
		ins_len += get_size_register_parameters(ins);
		ins_len += get_size_direct_parameters(ins);
		ins_len += get_size_indirect_parameters(ins);
		ins->length = ins_len;
		ins = ins->next;
	}
}
