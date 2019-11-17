/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feedme <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 12:54:40 by feedme            #+#    #+#             */
/*   Updated: 2019/03/12 03:13:04 by feedme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/vm.h"

void	checks_helper(t_process *current)
{
	t_process	*tmp;

	while (current->next)
	{
		if (current->next->nlive == 0)
		{
			tmp = current->next;
			current->next = current->next->next;
			tmp->next = NULL;
			free_process(&tmp);
			tmp = NULL;
		}
		else
			current->nlive = 0;
		if (current->next)
			current = current->next;
		else
			break ;
	}
	current->nlive = 0;
}

int		ft_time_for_checks(t_vm *vm)
{
	t_process	*current;
	t_process	*tmp;

	current = vm->process;
	if ((++vm->checks > MAX_CHECKS) || (vm->nlive >= NBR_LIVE))
	{
		vm->cycle_to_die -= CYCLE_DELTA;
		vm->checks = 0;
	}
	while (current && current->nlive == 0)
	{
		tmp = current;
		current = current->next;
		tmp->next = NULL;
		free_process(&tmp);
		vm->process = current;
		tmp = NULL;
	}
	if (current)
		checks_helper(current);
	vm->cycle = vm->cycle_to_die;
	if (!vm->process)
		return (-1);
	return (0);
}

int		handle_cycle(t_vm *vm)
{
	t_process	*current;

	current = vm->process;
	while (current)
	{
		current->c_to_wait--;
		current = current->next;
	}
	vm->tcycle++;
	vm->cycle--;
	vm->nbr_cycles--;
	return (vm->cycle > 0);
}

void	init_cycles(t_vm *vm, t_process *process)
{
	if ((vm->arena[process->index] > 18 || vm->arena[process->index] < 1) ||
		!validate_codingbyte(vm->arena[process->index],
		vm->arena[process->index + 1]))
		process->c_to_wait = 0;
	else
		process->c_to_wait = g_op_tab[vm->arena[process->index] - 1].nb_cycle;
}
