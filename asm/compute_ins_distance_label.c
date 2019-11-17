/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_ins_distance_label.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 01:17:43 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/03/13 17:28:28 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	get_distance_node_to_label_error_management(t_champ *champ, \
													char *label, int error_nb)
{
	if (error_nb == 0)
	{
		free(label);
		ft_syntax_error("the empty label is not a valid label", champ);
	}
	if (error_nb == 1)
	{
		free(label);
		ft_syntax_error("one of the label in a parameter does not exist", \
						champ);
	}
}

/*
**	This function computes the distance between the current instruction \
**	(which the param is part) and the label that is referred by this param.
**	It also checks if the label referred to in the parameter really exists.
*/

int		get_distance_node_to_label(t_champ *champ, t_ins *head, int node_nb, \
									char *label)
{
	int		i;
	int		node_val;
	int		label_val;
	t_ins	*tmp;

	tmp = head;
	node_val = 0;
	if ((i = 1) == 1 && label[0] == 0)
		get_distance_node_to_label_error_management(champ, label, 0);
	while (i < node_nb)
	{
		node_val += tmp->length;
		tmp = tmp->next;
		i++;
	}
	tmp = head;
	label_val = 0;
	while (tmp && ft_strcmp(label, tmp->label) != 0)
	{
		label_val += tmp->length;
		tmp = tmp->next;
	}
	if (tmp == NULL)
		get_distance_node_to_label_error_management(champ, label, 1);
	return (label_val - node_val);
}

/*
**	This function treats the 2 cases (direct or indirect param with label).
**	The 2 possib. of a reference to a label inside a parameter are listed \
**	in the if (a direct value starts with % and then the value or :label) \
**	and the else if (an indirect value starts directly with the value \
**	or :label in the case of a label).
**	We replace inside the parameter the reference to the label by \
**	the relative addressing up to this label.
*/

void	convert_label_to_dist_ins(t_champ *champ, t_ins *head, t_ins *ins, \
									char **par)
{
	char *label;
	char *dist;

	if (*par && (*par)[0] == DIRECT_CHAR
				&& ((*par)[0] != 0 && (*par)[1] == LABEL_CHAR))
	{
		label = ft_strdup(&((*par)[2]));
		dist = ft_itoa(get_distance_node_to_label(champ, head, ins->n, \
						label));
		free(*par);
		*par = ft_concat_one_char_and_one_string(DIRECT_CHAR, dist);
		free(label);
	}
	else if (*par && (*par)[0] == LABEL_CHAR)
	{
		label = ft_strdup(&((*par)[1]));
		dist = ft_itoa(get_distance_node_to_label(champ, head, ins->n, \
						label));
		free(*par);
		*par = ft_concat_strings("", dist, 2);
		free(label);
	}
}

/*
**	This function will convert the reference to a label inside a parameter \
**	to the distance between this parameter's instruction and the label that \
**	is referred (relative addressing).
*/

void	compute_ins_distance_label(t_champ *champ)
{
	t_ins *ins;
	t_ins *head;

	head = champ->ins;
	ins = champ->ins;
	while (ins)
	{
		if (ins->par1)
			convert_label_to_dist_ins(champ, head, ins, &(ins->par1));
		if (ins->par2)
			convert_label_to_dist_ins(champ, head, ins, &(ins->par2));
		if (ins->par3)
			convert_label_to_dist_ins(champ, head, ins, &(ins->par3));
		ins = ins->next;
	}
}
