/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_output_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 18:34:20 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/03/13 19:33:02 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
**	This function converts the name of the input file into the name of \
**	the new file.
**	Basicaly it replaces the extension of the input file by .cor.
**	The function first search for the last ., and then checks if there was \
**	a dot anyway. Then it concatenates everything that was before \
**	the last . with .cor to create the output file name.
*/

char	*convert_file_name(char *file_name)
{
	char	*new_file_name;
	int		i;
	char	*tmp;

	i = 0;
	while (file_name[i])
	{
		if (file_name[i] == '.'
				&& ft_strchr_nb(&file_name[i + 1], '.') == 0)
			break ;
		i++;
	}
	if (ft_strchr_nb(file_name, '.') == 0)
		i = 0;
	if (i == 0)
		tmp = ft_strdup("");
	else
		tmp = ft_strdup_nb(file_name, i);
	new_file_name = ft_concat_strings(tmp, ft_strdup(".cor"), 3);
	return (new_file_name);
}

/*
**	This function adds to the file the "magic code" that has to be \
**	at its beginning.
*/

void	add_magic_code(int fd)
{
	unsigned int	n;
	unsigned char	buf[4];

	n = COREWAR_EXEC_MAGIC;
	if (determine_computer_little_or_big_endian() == 'l')
	{
		buf[0] = ((unsigned char*)(&n))[3];
		buf[1] = ((unsigned char*)(&n))[2];
		buf[2] = ((unsigned char*)(&n))[1];
		buf[3] = ((unsigned char*)(&n))[0];
	}
	else
	{
		buf[0] = ((unsigned char*)(&n))[0];
		buf[1] = ((unsigned char*)(&n))[1];
		buf[2] = ((unsigned char*)(&n))[2];
		buf[3] = ((unsigned char*)(&n))[3];
	}
	if (write(fd, buf, 4) == -1)
		return ;
}

/*
**	This function adds the champion name to the file, then fills \
**	the remaining place dedicated to the champion name with 0, and then \
**	ads the 4 null-bytes buffer at the end of it.
**	It also checks that the champion name is not too long compared to \
**	the requirements.
*/

void	add_champion_name(t_champ *champ, int fd)
{
	unsigned char	buf[4];
	int				len;
	int				i;
	char			c;

	len = ft_strlen(champ->name);
	if (len > PROG_NAME_LENGTH)
		ft_syntax_error("the champion name is too long", champ);
	i = -1;
	while (++i < len)
		if (write(fd, &((champ->name)[i]), 1) == -1)
			return ;
	i--;
	c = 0;
	while (++i < PROG_NAME_LENGTH)
		if (write(fd, &c, 1) == -1)
			return ;
	buf[0] = 0;
	buf[1] = 0;
	buf[2] = 0;
	buf[3] = 0;
	if (write(fd, buf, 4) == -1)
		return ;
}

/*
**	This function adds the champion comment to the file, then fills \
**	the remaining place dedicated to the champion comment with 0, \
**	and then ads the 4 null-bytes buffer at the end of it.
**	It also checks that the champion comment is not too long compared \
**	to the requirements.
*/

void	add_champion_comment(t_champ *champ, int fd)
{
	unsigned char	buf[4];
	int				len;
	int				i;
	char			c;

	len = ft_strlen(champ->comment);
	if (len > COMMENT_LENGTH)
		ft_syntax_error("the champion comment is too long", champ);
	i = -1;
	while (++i < len)
		if (write(fd, &((champ->comment)[i]), 1) == -1)
			return ;
	i--;
	c = 0;
	while (++i < COMMENT_LENGTH)
		if (write(fd, &c, 1) == -1)
			return ;
	buf[0] = 0;
	buf[1] = 0;
	buf[2] = 0;
	buf[3] = 0;
	if (write(fd, buf, 4) == -1)
		return ;
}

/*
**	This function will first retrieve the name of the output file based on \
**	the name of the input file, then create this output file \
**	(overwriting a previous file with the same name), and then it will \
**	add to the file its different contents.
*/

void	create_output_file(t_champ *champ, char *file_name)
{
	int		fd;
	char	*new_file_name;

	new_file_name = convert_file_name(file_name);
	if ((fd = open(new_file_name, O_RDWR | O_CREAT | O_APPEND \
									| O_TRUNC, 0755)) == -1)
	{
		ft_putstr_fd("The creation of the .cor file has failed.\n", 2);
		return ;
	}
	add_magic_code(fd);
	add_champion_name(champ, fd);
	add_champion_length_to_output_file(champ, fd);
	add_champion_comment(champ, fd);
	add_champion_code_to_output_file(champ, fd);
	ft_putstr_fd("Writing output program to ", 1);
	ft_putstr_fd(new_file_name, 1);
	ft_putstr_fd("\n", 1);
	free(new_file_name);
	if (close(fd) == -1)
		return ;
}
