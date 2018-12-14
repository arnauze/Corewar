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
		p->header.comment[COMMENT_LENGTH] = '\0';
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

int		get_action(unsigned char *arena, unsigned int j, t_player *p)
{
	char *bit;
	int i;
	int add;

	add = 0;
	i = 0;
	if (!op_tab[arena[j] - 1].coding_byte)
		if (arena[j] == 1)
			add = 5;
		else
			add = 3;
	else
	{
		add += 2;
		bit = ft_char_to_bit((int)arena[j + 1]);
		while (bit[i])
		{
			if (bit[i] == '0' && bit[i + 1] == '1')
				add += 1;
			else if (bit[i] == '1' && bit[i + 1] == '1')
				add += 2;
			else if (bit[i] == '1' && bit[i + 1] == '0')
			{
				if (!op_tab[(int)arena[j] - 1].size)
					add += 4;
				else
					add += 2;
			}
			i += 2;
		}
	}
	p->action.size[p->action.track] = add;
	p->action.max++;
	return (p->action.size[p->action.track++]);
}

void	get_max_actions(unsigned char *arena, t_player *p)
{
	int count;
	int i;
	int add;
	int j;
	char *bit;

	i = 0;
	count = 0;
	while (i < (int)p->header.prog_size)
	{
		j = 0;
		add = 0;
		if (!op_tab[(int)arena[i] - 1].coding_byte)
			if (arena[i] == 1)
				add = 5;
			else
				add = 3;
		else
		{
			add += 2;
			bit = ft_char_to_bit((int)arena[i + 1]);
			while (bit[j])
			{
				if (bit[j] == '0' && bit[j + 1] == '1')
					add += 1;
				else if (bit[j] == '1' && bit[j + 1] == '1')
					add += 2;
				else if (bit[j] == '1' && bit[j + 1] == '0')
				{
					if (!op_tab[(int)arena[i] - 1].size)
						add += 4;
					else
						add += 2;
				}
				j += 2;
			}
		}
		i += add;
		count++;
	}
	p->action.size = (int *)malloc(sizeof(int) * (count + 1));
	i = 0;
	while (i <= count)
		p->action.size[i++] = 0;
}

void	get_player_actions(unsigned int i, t_player *p, unsigned char *arena)
{
	unsigned int	j;

	j = 0;
	get_max_actions(arena, p);
	while (j < i)
		j += get_action(arena, j, p);
	p->action.track = 0;
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

void			output_arena(t_vm vm)
{
	unsigned int	i;
	char			*t;

	i = 0;
	tputs(tgetstr("mr", NULL), 0, ft_putint);
	while (i < 2048)
	{
		if (i < vm.p1.header.prog_size)
			tputs(tgetstr("mr", NULL), 0, ft_putint);
		if (i == (unsigned int)vm.p1.index)
			tputs(tgetstr("me", NULL), 0, ft_putint);
		t = ft_itoa_base(vm.arena[i], 16, "0123456789abcdef");
		if (ft_strlen(t) < 2)
			ft_putchar('0');
		ft_putstr(t);
		if ((i + 1) % 64 == 0)
			ft_putchar('\n');
		else
			ft_putchar(' ');
		i++;
		if (i >= vm.p1.header.prog_size)
			tputs(tgetstr("me", NULL), 0, ft_putint);
	}
	while (i < 4096)
	{
		if (i - 2048 < vm.p2.header.prog_size)
			tputs(tgetstr("mr", NULL), 0, ft_putint);
		if (i == (unsigned int)vm.p2.index)
			tputs(tgetstr("me", NULL), 0, ft_putint);
		t = ft_itoa_base(vm.arena[i], 16, "0123456789abcdef");
		if (ft_strlen(t) < 2)
			ft_putchar('0');
		ft_putstr(t);
		if ((i + 1) % 64 == 0)
			ft_putchar('\n');
		else
			ft_putchar(' ');
		i++;
		if (i - 2048 >= vm.p2.header.prog_size)
			tputs(tgetstr("me", NULL), 0, ft_putint);
	}
}

void			initialize_players(t_player *p1, t_player *p2)
{
	p1->c_to_wait = 0;
	p1->index = 0;
	p1->action.max = 0;
	p1->action.size = NULL;
	p1->action.track = 0;
	p2->c_to_wait = 0;
	p2->index = 0;
	p2->action.max = 0;
	p2->action.size = NULL;
	p2->action.track = 0;
}

unsigned char	*ft_read_files(char **argv, t_player *p1, t_player *p2)
{
	unsigned char	*arena;

	initialize_players(p1, p2);
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

void	init_vm(t_vm *vm, char **argv)
{
	vm->cycle_to_die = CYCLE_TO_DIE;
	vm->cycle = vm->cycle_to_die;
	vm->checks = 0;
	vm->decrease = 0;
	vm->live = 0;
	vm->term = get_terminal();
	vm->arena = ft_read_files(argv, &vm->p1, &vm->p2);
	terminal_on(&vm->term);
}

void	handle_cycle(t_vm *vm)
{
	if (--vm->cycle == 0)
	{
		if (++vm->checks == MAX_CHECKS)
		{
			if (vm->decrease == 0)
				vm->cycle_to_die -= CYCLE_DELTA;
			else
				vm->decrease = 0;
			vm->checks = 0;
		}
		if (vm->live >= NBR_LIVE)
		{
			vm->cycle_to_die -= CYCLE_DELTA;
			vm->checks = 0;
			vm->decrease++;
		}
		vm->live = 0;
		vm->cycle = vm->cycle_to_die;
	}
}

void	handle_index_and_track(t_vm *vm)
{
	vm->p1.index = (vm->p1.index + vm->p1.action.size[vm->p1.action.track])
					% vm->p1.header.prog_size;
	vm->p2.index += vm->p2.action.size[vm->p2.action.track];
	if (vm->p2.index == vm->p2.header.prog_size + 2048)
		vm->p2.index = 2048;
	if (++vm->p1.action.track == vm->p1.action.max)
		vm->p1.action.track = 0;
	if (++vm->p2.action.track == vm->p2.action.max)
		vm->p2.action.track = 0;
}

void	start_vm(t_vm vm)
{
	while (1)
	{
		output_arena(vm);
		if (vm.arena[vm.p1.index] == 1)
			vm.live++;
		if (vm.arena[vm.p2.index] == 1)
			vm.live++;
		receive_key(&vm.term);
		handle_index_and_track(&vm);
		handle_cycle(&vm);
	}
}

int		main(int argc, char **argv)
{
	t_vm	vm;

	init_vm(&vm, argv);;
	terminal_on(&vm.term);
	if (argc > 1)
	{
		init_vm(&vm, argv);
		start_vm(vm);
		terminal_off(&vm.term);
	}
	return (0);
}