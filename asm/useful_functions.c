/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 16:54:51 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/03/11 14:27:39 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		ft_strlen(char *str)
{
	int n;

	n = 0;
	while (str[n])
		n++;
	return (n);
}

char	*ft_strdup(char *str)
{
	char	*new;
	int		len;
	int		i;

	len = ft_strlen(str);
	new = NULL;
	if (!(new = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = -1;
	while (++i < len)
		new[i] = str[i];
	new[len] = 0;
	return (new);
}

char	*ft_trim_begin(char *str)
{
	char	*new;
	char	*tmp;

	tmp = str;
	while (*str == 9 || *str == 11 || *str == 32)
		str++;
	new = ft_strdup(str);
	free(tmp);
	return (new);
}

int		ft_strchr_nb(char *str, char c)
{
	int n;

	n = 0;
	while (*str)
	{
		if (*str == c)
			n++;
		str++;
	}
	return (n);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
