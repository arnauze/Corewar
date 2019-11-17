/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_name_and_comment_champion.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 21:54:26 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/03/14 10:56:02 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
**	In this funciton we will retrieve the exact .name and store its value \
**	in the champ structure.
**	The check about a possible " that would appear in the comment after \
**	the .name and value declaration is done at some other part \
**	of the code, see function check_four_valid_quote_signs.
**	check_wrong_element_before_value allows to check if there is some \
**	random value between the .name and the value which is between "".
**	N.B.: when in the comment we talk about ".name" and ".comment", \
**	it corresponds to the macros NAME_CMD_STRING and COMMENT_CMD_STRING \
**	of the file op.h. Hence these values may be modified in the future...
*/

void	regularize_name(t_champ *champ, char *str)
{
	char	*tmp;
	char	*new;
	int		len;
	int		i;

	if (ft_strchr_nb(str, '"') == 1)
		ft_syntax_error("not enough \" signs for the name", champ);
	tmp = str;
	check_wrong_element_before_value(champ, tmp, \
										ft_strlen(NAME_CMD_STRING));
	while (*str != '"' && (len = 0) == 0)
		str++;
	str++;
	while (str[len] && str[len] != '"')
		len++;
	if (!(new = (char*)malloc(sizeof(char) * (len + 1))))
		return ;
	i = -1;
	while (++i < len)
		new[i] = str[i];
	new[len] = 0;
	champ->name = new;
	check_wrong_element_after_value(champ, tmp, \
										ft_strlen(NAME_CMD_STRING));
	free(tmp);
}

/*
**	The char *line is freed inside the ft_trim_begin function
**	we check that ft_strchr_nb(str, '"') == 0 as there has to be " on \
**	the same line as the .name
*/

void	get_name_champion(t_champ *champ, int fd)
{
	char	*line;
	char	*str;
	int		ret;

	while ((ret = get_next_line(fd, &line)) == 1)
	{
		str = ft_trim_begin(line);
		if (ft_strcmp_nb(NAME_CMD_STRING, str, \
				ft_strlen(NAME_CMD_STRING)) == 1)
			break ;
		free(str);
	}
	if (ret == 0)
		ft_syntax_error("there is no name field", champ);
	if (ft_strchr_nb(str, '"') == 0)
	{
		free(str);
		ft_syntax_error("not the right number of \" signs for the name", champ);
	}
	while (ft_strchr_nb(str, '"') < 2 && get_next_line(fd, &line) == 1)
	{
		str = ft_concat_strings(str, "\n", 1);
		str = ft_concat_strings(str, line, 3);
	}
	regularize_name(champ, str);
}

/*
**	check corresponding function for .name above.
*/

void	regularize_comment(t_champ *champ, char *str)
{
	char	*tmp;
	char	*new;
	int		len;
	int		i;

	if (ft_strchr_nb(str, '"') == 1)
		ft_syntax_error("not enough \" signs for the comment", champ);
	tmp = str;
	check_wrong_element_before_value(champ, tmp, \
										ft_strlen(COMMENT_CMD_STRING));
	while (*str != '"' && (len = 0) == 0)
		str++;
	str++;
	while (str[len] && str[len] != '"')
		len++;
	if (!(new = (char*)malloc(sizeof(char) * (len + 1))))
		return ;
	i = -1;
	while (++i < len)
		new[i] = str[i];
	new[len] = 0;
	champ->comment = new;
	check_wrong_element_after_value(champ, tmp, \
										ft_strlen(COMMENT_CMD_STRING));
	free(tmp);
}

/*
**	check corresponding function for .name above.
*/

void	get_comment_champion(t_champ *champ, int fd)
{
	char	*line;
	char	*str;
	int		ret;

	while ((ret = get_next_line(fd, &line)) == 1)
	{
		str = ft_trim_begin(line);
		if (ft_strcmp_nb(COMMENT_CMD_STRING, str, \
				ft_strlen(COMMENT_CMD_STRING)) == 1)
			break ;
		free(str);
	}
	if (ret == 0)
		ft_syntax_error("there is no comment field", champ);
	if (ft_strchr_nb(str, '"') == 0)
	{
		free(str);
		ft_syntax_error("not the right number of \" signs for the com.", champ);
	}
	while (ft_strchr_nb(str, '"') < 2 && get_next_line(fd, &line) == 1)
	{
		str = ft_concat_strings(str, "\n", 1);
		str = ft_concat_strings(str, line, 3);
	}
	regularize_comment(champ, str);
}

void	get_name_and_comment_champion(t_champ *champ, t_fd *std, char *path)
{
	int		fd1;
	int		fd2;

	if ((fd1 = open(path, O_RDONLY)) == -1)
		return ;
	if ((fd2 = open(path, O_RDONLY)) == -1)
		return ;
	get_name_champion(champ, fd1);
	get_comment_champion(champ, fd2);
	std->fd2 = fd1;
	std->fd3 = fd2;
	check_no_elements_before_end_name_and_comment(champ, std, path);
}
