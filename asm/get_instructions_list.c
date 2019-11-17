/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_instructions_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 17:51:15 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/03/13 17:18:21 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
**	With this function, we skip the 4 valid quotes that correspond to the \
**	definition of the .name and the .comment.
*/

void	move_to_first_instruction(int fd)
{
	char	c;

	find_next_opening_quote_sign(fd);
	find_next_closing_quote_sign(fd);
	find_next_opening_quote_sign(fd);
	find_next_closing_quote_sign(fd);
	while (read(fd, &c, 1))
	{
		if (c == '\n')
			break ;
	}
}

/*
**	This function creates the node that will contain the instruction and/or \
**	the label available on the line.
**	It adds the ins node created to the ins list and return this node \
**	so that it will get filled properly afterwards.
**	We put 0 as the default value for the ins_code, so that we can \
**	distinguish the nodes than contain just a label and no instruction \
**	(which have ins_code 0 vs. the nodes that have an instruction with \
**	ins_code of 1 and above).
*/

t_ins	*add_ins_node_to_list(t_champ *champ, int n)
{
	t_ins *new;
	t_ins *tmp;

	if (!(new = (t_ins*)malloc(sizeof(t_ins))))
		return (NULL);
	new->label = NULL;
	new->ins_code = 0;
	new->par1 = NULL;
	new->par2 = NULL;
	new->par3 = NULL;
	new->length = 0;
	new->n = n;
	new->next = NULL;
	if (champ->ins == NULL && (champ->ins = new) != NULL)
		return (new);
	tmp = champ->ins;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (new);
}

/*
**	This function checks is there is a label at the beginning of the line.
**	For that we move forward the line as long as we have chars that are \
**	among those that can be used for a label, then we check if the char \
**	coming after is the LABEL_CHAR (here : ), if this is the case then we have \
**	a label in this line and its value is the element before the LABEL_CHAR.
**	We add the label to the ins node.
*/

char	*add_label_to_node(t_ins *ins, char *str)
{
	int		n;

	n = 0;
	while (str[n] && ft_strchr_nb(LABEL_CHARS, str[n]) == 1)
		n++;
	if (str[n] != LABEL_CHAR)
		return (str);
	ins->label = ft_strdup_nb(str, n);
	if (str[n])
		n++;
	while (str[n] == 9 || str[n] == 11 || str[n] == 32)
		n++;
	return (&str[n]);
}

/*
**	We will store all the instructions of the file into a ins structure.
**	the check_not_empty_line function checks if a line does not contain \
**	anything or just a comment (then we would consider the line as empty).
**	we use the strtofree element of the ins structure as a way to keep \
**	track of a string that we want to free if we encounter an error \
**	inside the add_ins_to_node subfunction.
*/

void	put_instructions_and_labels_into_list(t_champ *champ, int fd)
{
	char	*line;
	char	*str;
	char	*tmp;
	t_ins	*ins;
	int		n;

	n = 1;
	while (get_next_line(fd, &line) == 1)
	{
		if (ft_check_not_empty_line(line) == 1)
		{
			str = ft_trim_begin(line);
			tmp = str;
			champ->strtofree = tmp;
			ins = add_ins_node_to_list(champ, n);
			str = add_label_to_node(ins, str);
			add_ins_to_node(champ, ins, str);
			free(tmp);
			champ->strtofree = NULL;
			n++;
		}
		else
			free(line);
	}
}

void	get_instructions_list(t_champ *champ, t_fd *std, char *path)
{
	int		fd;

	if ((fd = open(path, O_RDONLY)) == -1)
		return ;
	move_to_first_instruction(fd);
	put_instructions_and_labels_into_list(champ, fd);
	std->fd5 = fd;
}
