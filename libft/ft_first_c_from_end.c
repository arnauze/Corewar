/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_first_c_from_end.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 18:11:31 by amagnan           #+#    #+#             */
/*   Updated: 2019/03/15 14:21:40 by feedme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_first_c_from_end(char *str, char c)
{
	int	len;

	len = ft_strlen(str);
	while (--len > -1)
	{
		if (str[len] == c)
			return (len);
	}
	return (-1);
}
