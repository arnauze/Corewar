/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 14:07:18 by amagnan           #+#    #+#             */
/*   Updated: 2019/03/08 16:28:52 by feedme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/vm.h"

int		is_process_index(unsigned int i, t_process *head)
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

void	add_end_string(int x, int i)
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
	printw("  |\n| ");
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

void	add_informations(t_vm *vm)
{
	int i;

	i = 4;
	(void)vm;
	mvprintw(6, 202, "Total cycle: %d", vm->tcycle);
	mvprintw(7, 202, "Cycle to die: %d", vm->cycle);
	mvprintw(8, 202, "Live count: %d", vm->nlive);
	mvprintw(15, 202, "Player 1:");
	mvprintw(16, 202, "Name: %s", vm->p1->header.prog_name);
	mvprintw(17, 202, "Comment: %s", vm->p1->header.comment);
	mvprintw(25, 202, "Player 2:");
	mvprintw(26, 202, "Name: %s", vm->p2->header.prog_name);
	mvprintw(27, 202, "Comment: %s", vm->p2->header.comment);
	if (vm->p1->last_live)
		mvprintw(32, 202, "A process shows that player %d (%s) is alive",
		get_ind(0, vm->p1->nbr, 4), vm->p1->header.prog_name);
	if (vm->p2->last_live)
		mvprintw(32, 202, "A process shows that player %d (%s) is alive",
		get_ind(0, vm->p2->nbr, 4), vm->p2->header.prog_name);
}

void	output_arena(t_vm *vm)
{
	unsigned int	i;

	helper();
	i = -1;
	while (++i < 65 * 3 - 1)
		addch('-');
	addch('\n');
	printw("| ");
	i = 0;
	while (i < 2048)
		helper2(vm, &i);
	while (i < 4096)
		helper3(vm, &i);
	i = -1;
	while (++i < 65 * 3 - 1)
		addch('-');
	add_informations(vm);
	refresh();
}
