/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 15:11:07 by amagnan           #+#    #+#             */
/*   Updated: 2018/12/03 15:11:09 by amagnan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include "../header/vm.h"

char	*ft_get_file(char **argv, int x)
{
	int	i;
	int	c;

	c = 0;
	i = 0;
	if (x == 1)
	{
		while (argv[++i])
		{
			if (ft_strstr(argv[i], ".cor"))
				return (argv[i]);
		}
	}
	else if (x == 2)
	{
		while (argv[++i])
		{
			if (ft_strstr(argv[i], ".cor"))
			{
				if (++c == 2)
					return (argv[i]);
			}
		}
	}
	return (NULL);
}

void	get_comment(int fd, t_player *p)
{
	char	trash[4];

	if (read(fd, p->header.comment, COMMENT_LENGTH))
	{
		p->header.comment[COMMENT_LENGTH] = '\0';
	}
	read(fd, trash, 4);
}

void	get_name_and_size(int fd, t_player *p)
{
	char	buf[5];
	char	*part1;
	char	*part2;
	char	*part3;
	char	*part4;
	char	*tmp;

	if (read(fd, p->header.prog_name, PROG_NAME_LENGTH))
		p->header.prog_name[PROG_NAME_LENGTH] = '\0';
	read(fd, buf, 4);
	ft_bzero(buf, ft_strlen(buf));
	if (read(fd, buf, 4))
	{
		buf[4] = '\0';
		part1 = ft_itoa_base(buf[0], 16, "0123456789abcdef");
		part2 = ft_itoa_base(buf[1], 16, "0123456789abcdef");
		part3 = ft_itoa_base(buf[2], 16, "0123456789abcdef");
		part4 = ft_itoa_base(buf[3], 16, "0123456789abcdef");
		tmp = ft_strfjoin(ft_strjoin(part1, part2), ft_strjoin(part3, part4));
		p->header.prog_size = (unsigned int)ft_hex_to_decimal(tmp);
		ft_strdel(&tmp);
	}
}

void	get_magic_header(int fd, t_player *p)
{
	char	buf[5];

	if (read(fd, buf, 4) > 0)
		p->header.magic = (unsigned int)ft_hex_to_decimal("ea83f3");
}

void	get_executable(int fd, t_player *p, char *arena)
{
	unsigned int	i;

	if ((i = read(fd, arena, p->header.prog_size)) < p->header.prog_size)
		ft_exit_msg("Couldn't read the executable properly\n");
	while (i < 2048)
		arena[i++] = 0;
}

int		ft_get_player(int fd, t_player *p, char *arena)
{
	get_magic_header(fd, p);
	get_name_and_size(fd, p);
	get_comment(fd, p);
	get_executable(fd, p, arena);
	return (1);
}

char	*ft_read_files(char **argv, t_player *p1, t_player *p2)
{
	int	fd1;
	int	fd2;
	char	*arena;
	int	i = 0;
	int fff;

	fff = open("t.cor", O_RDWR);
	arena = ft_strnew(4096);
	if (((fd1 = open(ft_get_file(argv, 1), O_RDONLY)) < 0)
		|| (fd2 = open(ft_get_file(argv, 2), O_RDONLY)) < 0)
		ft_exit_msg("File can't be open\n");
	if (!ft_get_player(fd1, p1, arena) || !ft_get_player(fd2, p2, arena))
		ft_exit_msg("File error\n");
	while (i < 4096)
		ft_putchar_fd(arena[i++], fff);
	return (arena);
}

int		main(int argc, char **argv)
{
	t_player	p1;
	t_player	p2;
	char		*arena;

	if (argc > 1)
	{
		arena = ft_read_files(argv, &p1, &p2);
	}
	return (0);
}