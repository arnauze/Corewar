/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feedme <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 02:23:50 by feedme            #+#    #+#             */
/*   Updated: 2019/03/12 03:13:43 by feedme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/vm.h"

void	helper(void)
{
	clear();
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_RED);
	init_pair(2, COLOR_WHITE, COLOR_BLUE);
	init_pair(3, COLOR_BLACK, COLOR_WHITE);
	printw("\t\t\t\t\t\t\t\t\t\t*****DOOMLAND*****\t\t\t\t\t\t\t\t\t\n");
}

void	helper2(t_vm *vm, unsigned int *i)
{
	int		m;
	char	*t;

	m = 0;
	if (*i < vm->p1->header.prog_size &&
	!is_process_index(*i, vm->process) && (m = 1))
		attron(COLOR_PAIR(1));
	if (is_process_index(*i, vm->process) && (m = 2))
		attron(COLOR_PAIR(3));
	t = ft_itoa_base(vm->arena[*i], 16, "0123456789abcdef");
	if (ft_strlen(t) < 2)
		addch('0');
	printw(t);
	free(t);
	if ((*i + 1) % 64 == 0)
		add_end_string(m, *i);
	else
		addch(' ');
	(*i)++;
	if (*i <= vm->p1->header.prog_size && !is_process_index(*i, vm->process))
		attroff(COLOR_PAIR(1));
	if (is_process_index(*i - 1, vm->process))
		attroff(COLOR_PAIR(3));
}

void	helper3(t_vm *vm, unsigned int *i)
{
	int		m;
	char	*t;

	m = 0;
	if (*i - 2048 < vm->p2->header.prog_size &&
	!is_process_index(*i, vm->process) && (m = 1))
		attron(COLOR_PAIR(2));
	if (is_process_index(*i, vm->process) && (m = 2))
		attron(COLOR_PAIR(3));
	t = ft_itoa_base(vm->arena[*i], 16, "0123456789abcdef");
	if (ft_strlen(t) < 2)
		addch('0');
	printw(t);
	free(t);
	if ((*i + 1) % 64 == 0)
		add_end_string(m, *i);
	else
		addch(' ');
	(*i)++;
	if (*i - 2048 <= vm->p2->header.prog_size &&
	!is_process_index(*i, vm->process))
		attroff(COLOR_PAIR(2));
	if (is_process_index(*i - 1, vm->process))
		attroff(COLOR_PAIR(3));
}
