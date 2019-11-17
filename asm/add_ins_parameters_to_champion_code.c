/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_ins_parameters_to_champion_code.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 21:15:28 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/03/13 18:11:47 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	determine_computer_little_or_big_endian(void)
{
	int		i;
	char	*c;

	i = 1;
	c = (char*)(&i);
	if (c[0] == 1)
		return ('l');
	else
		return ('b');
}

void	add_ins_parameters_one_byte_long(int fd, int i)
{
	unsigned char c;

	i = i % 256;
	c = (unsigned char)i;
	if (write(fd, &c, 1) == -1)
		return ;
}

/*
**	This function converts the int 32 bytes into an int 16 before taking \
**	its bytes separately. It is to do the same as the example assembler \
**	that was provided.
**	In the code of the champion, the 2 and 4 bytes parameters are stored \
**	in big endian order. Some compueters are little endian, and so we have \
**	to test for the computer endianness and we have thus 2 cases for \
**	the 2 following functions.
*/

void	add_ins_parameters_two_bytes_long(int fd, int i, char endian)
{
	char	buf[2];
	int16_t	j;

	j = (int16_t)i;
	if (endian == 'l')
	{
		buf[0] = ((char*)(&j))[1];
		buf[1] = ((char*)(&j))[0];
	}
	if (endian == 'b')
	{
		buf[0] = ((char*)(&j))[0];
		buf[1] = ((char*)(&j))[1];
	}
	if (write(fd, buf, 2) == -1)
		return ;
}

void	add_ins_parameters_four_bytes_long(int fd, int i, char endian)
{
	char buf[4];

	if (endian == 'l')
	{
		buf[0] = ((char*)(&i))[3];
		buf[1] = ((char*)(&i))[2];
		buf[2] = ((char*)(&i))[1];
		buf[3] = ((char*)(&i))[0];
	}
	if (endian == 'b')
	{
		buf[0] = ((char*)(&i))[0];
		buf[1] = ((char*)(&i))[1];
		buf[2] = ((char*)(&i))[2];
		buf[3] = ((char*)(&i))[3];
	}
	if (write(fd, buf, 4) == -1)
		return ;
}

/*
**	This function transforms one specific instruction parameter into its \
**	corresponding bytes (1, 2 or 4) that are added to the output file.
*/

void	add_ins_parameters_to_champion_code(int ins_code, char *par, int fd)
{
	int		i;
	char	endian;

	endian = determine_computer_little_or_big_endian();
	i = 0;
	if (par && (par[0] == 'r' || par[0] == DIRECT_CHAR))
		i = ft_atoi(par + 1);
	else if (par && (par[0] != 'r' && par[0] != DIRECT_CHAR))
		i = ft_atoi(par);
	if (par)
	{
		if (par[0] == DIRECT_CHAR && (g_op_tab[ins_code - 1]).dir_size == 0)
			add_ins_parameters_four_bytes_long(fd, i, endian);
		else if ((par[0] == DIRECT_CHAR \
						&& (g_op_tab[ins_code - 1]).dir_size == 1)
					|| (par[0] != DIRECT_CHAR && par[0] != 'r'))
			add_ins_parameters_two_bytes_long(fd, i, endian);
		else if (par[0] == 'r')
			add_ins_parameters_one_byte_long(fd, i);
	}
}
