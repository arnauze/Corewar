/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 18:33:13 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/03/12 18:36:13 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
**	This function checks if the file passed as argument exists \
**	and if it is of the form file .s
*/

int		check_format_input_file(char *file_name)
{
	int fd;
	int i;

	if ((fd = open(file_name, O_RDONLY)) == -1)
		return (0);
	close(fd);
	if (ft_strchr_nb(file_name, '.') == 0)
		return (0);
	i = 0;
	while (file_name[i])
	{
		if (file_name[i] == '.'
				&& ft_strchr_nb(&file_name[i + 1], '.') == 0)
			break ;
		i++;
	}
	if (file_name[i + 1] != 's'
		|| (file_name[i + 1] != 0 && file_name[i + 2] != 0))
		return (0);
	return (1);
}
