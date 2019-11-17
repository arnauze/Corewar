/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful_functions_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 12:52:12 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/03/13 12:36:41 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_putstr_fd(char *str, int fd)
{
	if (str == NULL)
	{
		ft_putchar_fd('(', fd);
		ft_putchar_fd('n', fd);
		ft_putchar_fd('u', fd);
		ft_putchar_fd('l', fd);
		ft_putchar_fd('l', fd);
		ft_putchar_fd(')', fd);
		ft_putchar_fd('\n', fd);
		return ;
	}
	while (*str)
	{
		ft_putchar_fd(*str, fd);
		str++;
	}
	ft_putchar_fd('\n', fd);
}

char	*ft_concat_strings(char *s1, char *s2, int freed)
{
	char	*new;
	int		l1;
	int		l2;
	int		i1;
	int		i2;

	if (!s1)
		return (s2);
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	if (!(new = (char*)malloc(sizeof(char) * (l1 + l2 + 1))))
		return (NULL);
	i1 = -1;
	while (++i1 < l1)
		new[i1] = s1[i1];
	i2 = -1;
	while (++i2 < l2)
		new[l1 + i2] = s2[i2];
	new[l1 + l2] = 0;
	if (freed == 1 || freed == 3)
		free(s1);
	if (freed == 2 || freed == 3)
		free(s2);
	return (new);
}

void	ft_syntax_error(char *str, t_champ *champ)
{
	if (str)
	{
		free_champ_node(champ);
		ft_putstr_fd("syntax error: ", 2);
		ft_putstr_fd(str, 2);
		ft_putchar_fd('\n', 2);
	}
	else
	{
		free_champ_node(champ);
		ft_putstr_fd("syntax error\n", 2);
	}
	system("leaks asm");
	exit(0);
}

int		ft_check_not_empty_line(char *str)
{
	while (*str)
	{
		if (*str != 9 && *str != 11 && *str != 32)
		{
			if (*str == COMMENT_CHAR)
				return (0);
			else
				return (1);
		}
		str++;
	}
	return (0);
}

char	*ft_strdup_nb(char *str, int max)
{
	char	*new;
	int		len;
	int		i;

	len = ft_strlen(str);
	if (max < len)
		len = max;
	new = NULL;
	if (!(new = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = -1;
	while (++i < max)
		new[i] = str[i];
	new[len] = 0;
	return (new);
}
