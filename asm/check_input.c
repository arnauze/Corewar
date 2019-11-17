/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 16:50:42 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/03/12 15:32:12 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
**	This function is used inside the check_valid_param function to check if \
**	a parameter contains just special characters (r for register, % for \
**	direct char), a possible negative sign, and then numbers.
**	If it's not the case, then the parameter should not be considered as valid.
**	Normally, at this point, we should have a param != NULL when entering \
**	this function. Still, we put a test to be sure not to segfault.
*/

int		check_valid_number_format_in_param(char *param)
{
	int i;
	int flag;

	if (!param)
		return (1);
	i = 0;
	if (param[i] == 'r' || param[i] == DIRECT_CHAR)
		i++;
	if (param[i] == '-')
		i++;
	flag = 0;
	while (param[i])
	{
		if (param[i] < '0' || param[i] > '9')
			return (0);
		flag = 1;
		i++;
	}
	if (flag == 0)
		return (0);
	return (1);
}

/*
**	The 2 functions below check that when the .name and .comment declarations \
**	are not terminated (after 4 valid quotes), we don't have lines \
**	before that that contain something else than a comment.
**	At this time, due to previous checks, we know that the .name \
**	and .comment lines exist and that there are 4 valid quotes that \
**	are linked to their declaration. That's why, there are some checks \
**	that we don't need to do in the function below.
*/

int		check_and_skip_name_or_comment_section(int fd, char *line)
{
	int ret;
	int count;

	if (ft_strcmp_nb(NAME_CMD_STRING, line, \
				ft_strlen(NAME_CMD_STRING)) != 1
			&& ft_strcmp_nb(COMMENT_CMD_STRING, line, \
				ft_strlen(COMMENT_CMD_STRING)) != 1)
		return (1);
	count = ft_strchr_nb(line, '"');
	free(line);
	if (count < 2)
	{
		line = NULL;
		while ((ret = get_next_line(fd, &line) == 1)
				&& (count += ft_strchr_nb(line, '"')) < 2)
			free(line);
		if (line)
			free(line);
	}
	if (count < 2)
		return (1);
	return (0);
}

void	check_no_elements_before_end_name_and_comment(t_champ *champ, \
														t_fd *std, char *path)
{
	int		fd;
	int		error;
	char	*line;

	if ((fd = open(path, O_RDONLY)) == -1)
		return ;
	while (get_next_line(fd, &line) == 1 && ft_check_not_empty_line(line) == 0)
		free(line);
	line = ft_trim_begin(line);
	error = check_and_skip_name_or_comment_section(fd, line);
	while (get_next_line(fd, &line) == 1 && ft_check_not_empty_line(line) == 0)
		free(line);
	line = ft_trim_begin(line);
	error += check_and_skip_name_or_comment_section(fd, line);
	if (error > 0)
		ft_syntax_error("non-valid elements before the end of the \
name and comment declaration", champ);
	std->fd4 = fd;
}

/*
**	this function allows to check if there is no strange value between \
**	the .name or .comment and their corresponding value which is between "".
*/

void	check_wrong_element_before_value(t_champ *champ, char *str, int len)
{
	int i;
	int j;

	i = len;
	j = 0;
	while (str[i] && str[i] != '"')
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\v')
		{
			free(str);
			ft_syntax_error("wrong element between .name or .comment and \
its corresponding value", champ);
		}
		i++;
	}
}

/*
**	Here we check that there is no invalid value at the end of the line \
**	of the .name or .comment declaration.
**	The only valid reason to have something else at the end of the declaration \
**	line would be to have a comment there (that would start with a #).
*/

void	check_wrong_element_after_value(t_champ *champ, char *str, int len)
{
	int count;
	int i;

	i = len;
	count = 0;
	while (count != 2)
	{
		if (str[i] == '"')
			count++;
		i++;
	}
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\v')
		i++;
	if (str[i] != 0 && str[i] != COMMENT_CHAR)
	{
		free(str);
		ft_syntax_error("wrong element after the .name or \
.comment value", champ);
	}
}
