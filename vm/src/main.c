/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Arnaud <Arnaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 15:11:07 by amagnan           #+#    #+#             */
/*   Updated: 2018/12/13 16:54:54 by Arnaud           ###   ########.fr       */
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

void	get_action(unsigned char *arena, unsigned int j, t_player *p)
{
	
	p->action.max++;
}

void	get_player_actions(unsigned int i, t_player *p, unsigned char *arena)
{
	unsigned int	j;

	j = 0;
	p->action.track = 0;
	p->action.max = 0;
	while (j < i)
		j = get_action(arena, j, p);
}

void	get_executable(int fd, t_player *p, unsigned char *arena)
{
	unsigned int	i;

	if ((i = read(fd, arena, p->header.prog_size)) < p->header.prog_size)
		ft_exit_msg("Couldn't read the executable properly\n");
	get_player_actions(i, p, arena);
	while (i < 2048)
		arena[i++] = 0;
}

int		ft_get_player(t_player *p, unsigned char *arena)
{
	get_magic_header(p->fd, p);
	get_name_and_size(p->fd, p);
	get_comment(p->fd, p);
	get_executable(p->fd, p, arena);
	return (1);
}

void			output_arena(unsigned char *arena, t_player p1, t_player p2)
{
	unsigned int	i;
	char			*t;
	(void)p2;
	i = 0;
	tputs(tgetstr("mr", NULL), 0, ft_putint);
	while (i < 2048)
	{
		if (i <= p1.header.prog_size)
			tputs(tgetstr("mr", NULL), 0, ft_putint);
		if (i == (unsigned int)p1.index)
			tputs(tgetstr("us", NULL), 0, ft_putint);
		t = ft_itoa_base(arena[i], 16, "0123456789abcdef");
		if (ft_strlen(t) < 2)
			ft_putchar('0');
		ft_putstr(t);
		if (i == (unsigned int)p1.index)
			tputs(tgetstr("ue", NULL), 0, ft_putint);
		if ((i + 1) % 64 == 0)
			ft_putchar('\n');
		else
			ft_putchar(' ');
		i++;
		if (i >= p1.header.prog_size)
			tputs(tgetstr("me", NULL), 0, ft_putint);
	}
	// tputs(tgetstr("mr", NULL), 0, ft_putint);
	// while (i < 4096)
	// {
	// 	if (i - 2048 == p2.header.prog_size)
	// 		tputs(tgetstr("me", NULL), 0, ft_putint);
	// 	if (i == (unsigned int)p2.index)
	// 		tputs(tgetstr("us", NULL), 0, ft_putint);
	// 	t = ft_itoa_base(arena[i], 16, "0123456789abcdef");
	// 	if (ft_strlen(t) < 2)
	// 		ft_putchar('0');
	// 	ft_putstr(t);
	// 	if ((i + 1) % 64 == 0)
	// 		ft_putchar('\n');
	// 	else
	// 		ft_putchar(' ');
	// 	if (i == (unsigned int)p2.index)
	// 		tputs(tgetstr("ue", NULL), 0, ft_putint);
	// 	i++;
	// }
}

unsigned char	*ft_read_files(char **argv, t_player *p1, t_player *p2)
{
	unsigned char	*arena;

	arena = (unsigned char *)ft_strnew(4096);
	if (((p1->fd = open(ft_get_file(argv, 1), O_RDONLY)) < 0)
		|| (p2->fd = open(ft_get_file(argv, 2), O_RDONLY)) < 0)
		ft_exit_msg("File can't be open\n");
	if (!ft_get_player(p1, arena) || !ft_get_player(p2, arena + 2048))
		ft_exit_msg("File error\n");
	p1->index = 0;
	p2->index = 2048;
	return (arena);
}

int		main(int argc, char **argv)
{
	t_player	p1;
	t_player	p2;
	t_term		term;
	unsigned char		*arena;

	term = get_terminal();
	terminal_on(&term);
	if (argc > 1)
	{
		arena = ft_read_files(argv, &p1, &p2);
		while (1)
		{
			output_arena(arena, p1, p2);
			receive_key(&term);
			if ((p1.index += p1.action.size[p1.action.track++]) > p1.header.prog_size)
				p1.index = 0;
			if (p1.action.track > p1.action.max)
				p1.action.track = 0;
		}
	}
	terminal_off(&term);
	return (0);
}