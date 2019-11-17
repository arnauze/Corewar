/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_ins_to_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 16:43:23 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/03/13 18:10:18 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	add_op_nb_to_node_sub_sub(t_ins *ins, char *op)
{
	if (ft_strcmp(op, "sti") == 0)
		ins->ins_code = 11;
	if (ft_strcmp(op, "fork") == 0)
		ins->ins_code = 12;
	if (ft_strcmp(op, "lld") == 0)
		ins->ins_code = 13;
	if (ft_strcmp(op, "lldi") == 0)
		ins->ins_code = 14;
	if (ft_strcmp(op, "lfork") == 0)
		ins->ins_code = 15;
	if (ft_strcmp(op, "aff") == 0)
		ins->ins_code = 16;
	if (ft_strcmp(op, "swap") == 0)
		ins->ins_code = 17;
	if (ft_strcmp(op, "wipe") == 0)
		ins->ins_code = 18;
}

void	add_op_nb_to_node_sub(t_ins *ins, char *op)
{
	if (ft_strcmp(op, "live") == 0)
		ins->ins_code = 1;
	if (ft_strcmp(op, "ld") == 0)
		ins->ins_code = 2;
	if (ft_strcmp(op, "st") == 0)
		ins->ins_code = 3;
	if (ft_strcmp(op, "add") == 0)
		ins->ins_code = 4;
	if (ft_strcmp(op, "sub") == 0)
		ins->ins_code = 5;
	if (ft_strcmp(op, "and") == 0)
		ins->ins_code = 6;
	if (ft_strcmp(op, "or") == 0)
		ins->ins_code = 7;
	if (ft_strcmp(op, "xor") == 0)
		ins->ins_code = 8;
	if (ft_strcmp(op, "zjmp") == 0)
		ins->ins_code = 9;
	if (ft_strcmp(op, "ldi") == 0)
		ins->ins_code = 10;
	add_op_nb_to_node_sub_sub(ins, op);
	free(op);
}

/*
**	This function add the ins_code corresponding to a specific instruction \
**	to the ins list node.
**	It also checks that the ins_code is not invalid (getting an ins_code \
**	of 0 at this point can only mean that there is an invalid ins name).
**	Then it moves to the first parameter.
*/

char	*add_op_nb_to_node(t_champ *champ, t_ins *ins, char *str)
{
	int		n;
	char	*op;

	n = 0;
	if (*str == 0)
		return (str);
	while (str[n] && str[n] != 9 && str[n] != 11 && str[n] != 32)
		n++;
	op = ft_strdup_nb(str, n);
	add_op_nb_to_node_sub(ins, op);
	if (ins->ins_code == 0)
		ft_syntax_error("There is a wrong op name", champ);
	if (str[n])
		n++;
	while (str[n] == 9 || str[n] == 11 || str[n] == 32)
		n++;
	return (&str[n]);
}

/*
**	This function puts into the ins list node the parameters of the ins \
**	instruction.
**	In the function we first skips the spaces and the commas separating \
**	two parameters.
**	We check that there is just one , separating 2 parameters also.
**	N.B.: comma is the default separator in corewar, but it could be replaced\
**	by another sign. See the file op.h for the SEPARATOR_CHAR macro.
*/

char	*add_param_to_node(t_champ *champ, t_ins *ins, int param_nb, char *str)
{
	int n;
	int count_separator;

	if (*str == 0)
		return (str);
	count_separator = 0;
	while (*str == 9 || *str == 11 || *str == 32 || *str == SEPARATOR_CHAR)
		if (*str++ == SEPARATOR_CHAR)
			count_separator++;
	if ((count_separator != 1 && param_nb > 1) \
		|| (count_separator != 0 && param_nb == 1))
		ft_syntax_error("not the right number of separators \
between some parameters", champ);
	n = 0;
	while (str[n] && str[n] != 9 && str[n] != 11 && str[n] != 32
			&& str[n] != SEPARATOR_CHAR && str[n] != COMMENT_CHAR)
		n++;
	if (param_nb == 1)
		ins->par1 = ft_strdup_nb(str, n);
	if (param_nb == 2)
		ins->par2 = ft_strdup_nb(str, n);
	if (param_nb == 3)
		ins->par3 = ft_strdup_nb(str, n);
	return (&str[n]);
}

/*
**	This function adds the instruction and params to the related node \
**	of the ins struct list.
**	We add the ins_code then the parameters and then we check that \
**	the remaining of the line is empty (i.e. contains just spaces, tabs \
**	or a comment).
**	Some lines can contain a label but no instruction, that's what \
**	we test with the first if statement.
*/

void	add_ins_to_node(t_champ *champ, t_ins *ins, char *str)
{
	if (*str == 0 || *str == COMMENT_CHAR)
		return ;
	str = add_op_nb_to_node(champ, ins, str);
	if ((g_op_tab[ins->ins_code - 1]).arg_nb > 0)
		str = add_param_to_node(champ, ins, 1, str);
	if ((g_op_tab[ins->ins_code - 1]).arg_nb > 1)
		str = add_param_to_node(champ, ins, 2, str);
	if ((g_op_tab[ins->ins_code - 1]).arg_nb > 2)
		str = add_param_to_node(champ, ins, 3, str);
	if (ft_check_not_empty_line(str) == 1)
		ft_syntax_error("there is a wrong element after the last param \
of an ins, or alternatively too many params for some instruction(s)", champ);
}
