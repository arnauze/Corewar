/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_champion_code_to_output_file.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 19:26:43 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/03/13 18:33:40 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	add_ins_code(t_ins *ins, int fd)
{
	unsigned char c;

	c = (unsigned char)(ins->ins_code);
	if (write(fd, &c, 1) == -1)
		return ;
}

/*
**	This function adds the coding byte to the file.
**	the coding byte contains information on the number of parameters for \
**	this specific instruction and also the type of these parameters.
**	the ifs below correspond to the different cases possible.
*/

void	add_coding_byte(t_ins *ins, int fd)
{
	unsigned char c;

	c = 0;
	if (ins->par1 && ins->par1[0] != 'r' && ins->par1[0] != DIRECT_CHAR)
		c += 64 * 3;
	if (ins->par1 && (ins->par1[0] == 'r' || ins->par1[0] == DIRECT_CHAR))
		c += 64 * ((ins->par1[0] == 'r') ? 1 : 2);
	if (ins->par2 && ins->par2[0] != 'r' && ins->par2[0] != DIRECT_CHAR)
		c += 16 * 3;
	if (ins->par2 && (ins->par2[0] == 'r' || ins->par2[0] == DIRECT_CHAR))
		c += 16 * ((ins->par2[0] == 'r') ? 1 : 2);
	if (ins->par3 && ins->par3[0] != 'r' && ins->par3[0] != DIRECT_CHAR)
		c += 4 * 3;
	if (ins->par3 && (ins->par3[0] == 'r' || ins->par3[0] == DIRECT_CHAR))
		c += 4 * ((ins->par3[0] == 'r') ? 1 : 2);
	if (write(fd, &c, 1) == -1)
		return ;
}

/*
**	This function will add the champion code to the output file.
**	To do so, it goes down the ins list and add the instructions \
**	(ins code, codyng byte, and parameters) one by one.
*/

void	add_champion_code_to_output_file(t_champ *champ, int fd)
{
	t_ins *ins;

	ins = champ->ins;
	while (ins)
	{
		if (ins->ins_code != 0)
		{
			add_ins_code(ins, fd);
			if ((g_op_tab[ins->ins_code - 1]).coding_byte == 1)
				add_coding_byte(ins, fd);
			add_ins_parameters_to_champion_code(ins->ins_code, \
					ins->par1, fd);
			add_ins_parameters_to_champion_code(ins->ins_code, \
					ins->par2, fd);
			add_ins_parameters_to_champion_code(ins->ins_code, \
					ins->par3, fd);
		}
		ins = ins->next;
	}
}
