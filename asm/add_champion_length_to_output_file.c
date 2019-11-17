/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_champion_length_to_output_file.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 16:42:37 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/03/13 19:33:04 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
**	This function computes the length of the champion which is here defined \
**	as the sum of the length of its different instructions (in number of \
**	bytes in the output file).
*/

int		compute_length_champion(t_champ *champ)
{
	int		len;
	t_ins	*ins;

	ins = champ->ins;
	len = 0;
	while (ins)
	{
		len += ins->length;
		ins = ins->next;
	}
	return (len);
}

/*
**	We don't check in this section if the champion is not too long as the \
**	assembler given as an example does not seem to return an error message \
**	for a very long champion. Such a check will thus be done when \
**	the champions will be used in the virtual machine.
**	This function adds the length of the champion to the output file, \
**	to do so, it converts the champion length which is contained inside \
**	an int into the value of the 4 bytes that constitute this int.
*/

void	add_champion_length_to_output_file(t_champ *champ, int fd)
{
	unsigned char	buf[4];
	int				len;

	len = compute_length_champion(champ);
	if (determine_computer_little_or_big_endian() == 'l')
	{
		buf[0] = ((unsigned char*)(&len))[3];
		buf[1] = ((unsigned char*)(&len))[2];
		buf[2] = ((unsigned char*)(&len))[1];
		buf[3] = ((unsigned char*)(&len))[0];
	}
	else
	{
		buf[0] = ((unsigned char*)(&len))[0];
		buf[1] = ((unsigned char*)(&len))[1];
		buf[2] = ((unsigned char*)(&len))[2];
		buf[3] = ((unsigned char*)(&len))[3];
	}
	if (write(fd, buf, 4) == -1)
		return ;
}
