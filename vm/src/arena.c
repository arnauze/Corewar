/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 14:07:18 by amagnan           #+#    #+#             */
/*   Updated: 2018/12/16 14:07:18 by amagnan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/vm.h"

int 			IS_PROCESS_INDEX(unsigned int i, t_process *head)
{
	t_process	*current;

	current = head;
	while (current)
	{
		if (current->index == i)
			return (1);
		current = current->next;
	}
	return (0);
}

void			ADD_END_STRING(int x, int i)
{
	if (x == 1)
	{
		if (i < 2048)
			attroff(COLOR_PAIR(1));
		else
			attroff(COLOR_PAIR(2));
	}
	else if (x == 2)
		attroff(COLOR_PAIR(3));
	printw("  |\n");
	if (x == 1)
	{
		if (i < 2048)
			attron(COLOR_PAIR(1));
		else
			attron(COLOR_PAIR(2));
	}
	else if (x == 2)
		attron(COLOR_PAIR(3));
}

void			output_arena(t_vm *vm)
{
	unsigned int	i;
	char			*t;
	int m;

	m = 0;
	clear();
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_RED);
	init_pair(2, COLOR_WHITE, COLOR_BLUE);
	init_pair(3, COLOR_BLACK, COLOR_WHITE);
	printw("\t\t\t\t\t\t\t\t\t\t*****DOOMLAND*****\t\t\t\t\t\t\t\t\t\n");
	i = -1;
	while (++i < 65 * 3 - 1)
		addch('-');
	addch('\n');
	i = 0;
	while (i < 2048)
	{
		m = 0;
		if (i < vm->p1.header.prog_size && !IS_PROCESS_INDEX(i, vm->process))
		{
			m = 1;
			attron(COLOR_PAIR(1));
		}
		if (IS_PROCESS_INDEX(i, vm->process))
		{
			m = 2;
			attron(COLOR_PAIR(3));
		}
		t = ft_itoa_base(vm->arena[i], 16, "0123456789abcdef");
		if (ft_strlen(t) < 2)
			addch('0');
		printw(t);
		if ((i + 1) % 64 == 0)
			ADD_END_STRING(m, i);
		else
			addch(' ');
		i++;
	 	if (i <= vm->p1.header.prog_size && !IS_PROCESS_INDEX(i, vm->process))
	 		attroff(COLOR_PAIR(1));
	 	if (IS_PROCESS_INDEX(i - 1, vm->process))
				attroff(COLOR_PAIR(3));
	}
	while (i < 4096)
	{
		m = 0;
		if (i - 2048 < vm->p2.header.prog_size && !IS_PROCESS_INDEX(i, vm->process))
		{
			m = 1;
			attron(COLOR_PAIR(2));
		}
		if (IS_PROCESS_INDEX(i, vm->process))
		{
			m = 2;
			attron(COLOR_PAIR(3));
		}
		t = ft_itoa_base(vm->arena[i], 16, "0123456789abcdef");
		if (ft_strlen(t) < 2)
			addch('0');
		printw(t);
		if ((i + 1) % 64 == 0)
			ADD_END_STRING(m, i);
		else
			addch(' ');
		i++;
		if (i - 2048 <= vm->p2.header.prog_size && !IS_PROCESS_INDEX(i, vm->process))
			attroff(COLOR_PAIR(2));
		if (IS_PROCESS_INDEX(i - 1, vm->process))
			attroff(COLOR_PAIR(3));
	}
	i = -1;
	while (++i < 65 * 3 - 1)
		addch('-');
	refresh();
}
