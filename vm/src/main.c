/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Arnaud <Arnaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 15:11:07 by amagnan           #+#    #+#             */
/*   Updated: 2018/12/14 06:40:14 by Arnaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include "../header/vm.h"

// int		get_action(unsigned char *arena, unsigned int j, t_player *p)
// {
// 	char *bit;
// 	int i;
// 	int add;

// 	add = 0;
// 	i = 0;
// 	if (!op_tab[arena[j] - 1].coding_byte)
// 		if (arena[j] == 1)
// 			add = 5;
// 		else
// 			add = 3;
// 	else
// 	{
// 		add += 2;
// 		bit = ft_char_to_bit((int)arena[j + 1]);
// 		while (bit[i])
// 		{
// 			if (bit[i] == '0' && bit[i + 1] == '1')
// 				add += 1;
// 			else if (bit[i] == '1' && bit[i + 1] == '1')
// 				add += 2;
// 			else if (bit[i] == '1' && bit[i + 1] == '0')
// 			{
// 				if (!op_tab[(int)arena[j] - 1].size)
// 					add += 4;
// 				else
// 					add += 2;
// 			}
// 			i += 2;
// 		}
// 	}
// 	p->action.size[p->action.track] = add;
// 	p->action.max++;
// 	return (p->action.size[p->action.track++]);
// }

// void	get_max_actions(unsigned char *arena, t_player *p)
// {
// 	int count;
// 	int i;
// 	int add;
// 	int j;
// 	char *bit;

// 	i = 0;
// 	count = 0;
// 	while (i < (int)p->header.prog_size)
// 	{
// 		j = 0;
// 		add = 0;
// 		if (!op_tab[(int)arena[i] - 1].coding_byte)
// 			if (arena[i] == 1)
// 				add = 5;
// 			else
// 				add = 3;
// 		else
// 		{
// 			add += 2;
// 			bit = ft_char_to_bit((int)arena[i + 1]);
// 			while (bit[j])
// 			{
// 				if (bit[j] == '0' && bit[j + 1] == '1')
// 					add += 1;
// 				else if (bit[j] == '1' && bit[j + 1] == '1')
// 					add += 2;
// 				else if (bit[j] == '1' && bit[j + 1] == '0')
// 				{
// 					if (!op_tab[(int)arena[i] - 1].size)
// 						add += 4;
// 					else
// 						add += 2;
// 				}
// 				j += 2;
// 			}
// 		}
// 		i += add;
// 		count++;
// 	}
// 	p->action.size = (int *)malloc(sizeof(int) * (count + 1));
// 	i = 0;
// 	while (i <= count)
// 		p->action.size[i++] = 0;
// }

// void	get_player_actions(unsigned int i, t_player *p, unsigned char *arena)
// {
// 	unsigned int	j;

// 	j = 0;
// 	get_max_actions(arena, p);
// 	while (j < i)
// 		j += get_action(arena, j, p);
// 	p->action.track = 0;
// }

// void	handle_cycle(t_vm *vm)
// {
// 	if (--vm->cycle == 0)
// 	{
// 		if (++vm->checks == MAX_CHECKS)
// 		{
// 			if (vm->decrease == 0)
// 				vm->cycle_to_die -= CYCLE_DELTA;
// 			else
// 				vm->decrease = 0;
// 			vm->checks = 0;
// 		}
// 		if (vm->live >= NBR_LIVE)
// 		{
// 			vm->cycle_to_die -= CYCLE_DELTA;
// 			vm->checks = 0;
// 			vm->decrease++;
// 		}
// 		vm->live = 0;
// 		vm->cycle = vm->cycle_to_die;
// 	}
// }

// void	handle_index_and_track(t_vm *vm)
// {
// 	vm->p1.index = (vm->p1.index + vm->p1.action.size[vm->p1.action.track])
// 					% vm->p1.header.prog_size;
// 	vm->p2.index += vm->p2.action.size[vm->p2.action.track];
// 	if (vm->p2.index == vm->p2.header.prog_size + 2048)
// 		vm->p2.index = 2048;
// 	if (++vm->p1.action.track == vm->p1.action.max)
// 		vm->p1.action.track = 0;
// 	if (++vm->p2.action.track == vm->p2.action.max)
// 		vm->p2.action.track = 0;
// }

// void		signal_handler(int sig)
// {
// 	t_vm	vm;

// 	vm = get_vm(NULL, NULL);
// 	if (sig == SIGINT || sig == SIGABRT || sig == SIGKILL
// 		|| sig == SIGQUIT || sig == SIGTSTP)
// 		endwin();
// 	// else if (sig == SIGWINCH)
// 	// {
// 	// 	tputs(tgetstr("cl", NULL), 0, ft_putint);
// 	// 	if (get_size(&vm.term) == -1)
// 	// 		ft_putstr("Not enough space\n");
// 	// 	else
// 	// 		output_arena(&vm);
// 	// }
// }

// void		initialize_signals(void)
// {
// 	signal(SIGTSTP, signal_handler);
// 	signal(SIGINT, signal_handler);
// 	signal(SIGABRT, signal_handler);
// 	signal(SIGKILL, signal_handler);
// 	signal(SIGQUIT, signal_handler);
// 	signal(SIGWINCH, signal_handler);
// }

int		main(int argc, char **argv)
{
	t_vm	vm;

	vm = get_vm(argv, NULL);
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	// initialize_signals();
	if (argc > 1)
	{
		start_vm(&vm);
		// terminal_off(&vm.term);
	}
	endwin();
	return (0);
}