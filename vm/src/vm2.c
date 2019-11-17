/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feedme <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 12:54:11 by feedme            #+#    #+#             */
/*   Updated: 2019/03/12 03:15:24 by feedme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/vm.h"

int		c_byte_size(unsigned char c_byte)
{
	char	*new;
	int		i;
	int		count;

	count = 0;
	i = 0;
	new = ft_char_to_bit((int)c_byte);
	while (i < 8)
	{
		if (!ft_strncmp(new + i, "10", 2))
			count += 4;
		else if (!ft_strncmp(new + i, "11", 2))
			count += 2;
		else if (!ft_strncmp(new + i, "01", 2))
			count += 1;
		i += 2;
	}
	free(new);
	return (count + 2);
}

int		validate_helper(unsigned char op_code, unsigned char c_byte)
{
	if (op_code == 6 || op_code == 7 || op_code == 8)
	{
		if (c_byte == 84 || c_byte == 148 || c_byte == 212 ||
		c_byte == 228 || c_byte == 164 || c_byte == 100 ||
		c_byte == 116 || c_byte == 244 || c_byte == 180)
			return (c_byte_size(c_byte));
	}
	else if (op_code == 10 || op_code == 14)
	{
		if (c_byte == 84 || c_byte == 212 || c_byte == 148 ||
		c_byte == 100 || c_byte == 164 || c_byte == 228)
			return (c_byte_size(c_byte));
	}
	else if (op_code == 11)
	{
		if (c_byte == 84 || c_byte == 88 || c_byte == 100 ||
		c_byte == 104 || c_byte == 120 || c_byte == 116)
			return (c_byte_size(c_byte));
	}
	else if (op_code == 16)
	{
		if (c_byte == 64)
			return (c_byte_size(c_byte));
	}
	return (0);
}

int		validate_codingbyte(unsigned char op_code, unsigned char c_byte)
{
	if (op_code == 1)
		return (5);
	else if (op_code == 18)
		return (1);
	else if (op_code == 9 || op_code == 12 || op_code == 15 || op_code == 17)
		return (3);
	else if (op_code == 2 || op_code == 13)
	{
		if (c_byte == 144 || c_byte == 208)
			return (c_byte_size(c_byte));
	}
	else if (op_code == 3)
	{
		if (c_byte == 80 || c_byte == 112)
			return (c_byte_size(c_byte));
	}
	else if (op_code == 4 || op_code == 5)
	{
		if (c_byte == 84)
			return (c_byte_size(c_byte));
	}
	else
		return (validate_helper(op_code, c_byte));
	return (0);
}
