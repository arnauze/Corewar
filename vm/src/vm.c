/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 14:03:55 by amagnan           #+#    #+#             */
/*   Updated: 2018/12/16 14:03:56 by amagnan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/vm.h"

t_vm	get_vm(char **argv, t_vm *new)
{
	static t_vm vm;

	if (argv && !new)
	{
		vm.process = NULL;
		vm.arena = ft_read_files(argv, &vm);
		vm.cycle_to_die = CYCLE_TO_DIE;
		vm.tcycle = 0;
		vm.cycle = vm.cycle_to_die;
		vm.checks = 0;
		vm.nlive = 0;
		vm.last_live = 0;
		initialize_process(&vm);
	}
	else
		if (new)
			vm = *new;
	return (vm);
}

int 	c_byte_size(unsigned char c_byte)
{
	char 	*new;
	int 	i;
	int count;

	count = 0;
	i = 0;
	new = ft_char_to_bit((int)c_byte);
	while (i < 8)
	{
		if (!ft_strncmp(new + i, "10", 2))
			count += 4;
		else if (!ft_strncmp(new + i, "11", 2))
			count += 2;
		else if (!ft_strncmp(new + i, "01", 2))
			count += 1;
		i += 2;
	}
	return (count + 2);
}

int		validate_codingbyte(unsigned char op_code, unsigned char c_byte)
{
	if (op_code == 1)
		return (5);
	else if (op_code == 9 || op_code == 12 || op_code == 15)
	{
		return (3);
	}
	else if (op_code == 2 || op_code == 13)
	{
		if (c_byte == 144 || c_byte == 208)
			return (c_byte_size(c_byte));
	}
	else if (op_code == 3)
	{
		if (c_byte == 80 || c_byte == 112)
			return (c_byte_size(c_byte));
	}
	else if (op_code == 4 || op_code == 5)
	{
		if (c_byte == 84)
			return (c_byte_size(c_byte));
	}
	else if (op_code == 6 || op_code == 7 || op_code == 8)
	{
		if (c_byte == 84 || c_byte == 148 || c_byte == 212 ||
		c_byte == 228 || c_byte == 164 || c_byte == 100 ||
		c_byte == 116 || c_byte == 244 || c_byte == 180)
			return (c_byte_size(c_byte));
	}
	else if (op_code == 10 || op_code == 14)
	{
		if (c_byte == 84 || c_byte == 212 || c_byte == 148 ||
		c_byte == 100 || c_byte == 164 || c_byte == 228)
			return (c_byte_size(c_byte));
	}
	else if (op_code == 11)
	{
		if (c_byte == 84 || c_byte == 88 || c_byte == 100 ||
		c_byte == 104 || c_byte == 120 || c_byte == 116)
			return (c_byte_size(c_byte));
	}
	else if (op_code == 16)
	{
		if (c_byte == 64)
			return (c_byte_size(c_byte));
	}
	return (0);
}

// int 	FT_IS_ACTION(unsigned char *arena, int index)
// {
// 	char	*bit;
// 	int 	i;
// 	int 	c;

// 	i = 0;
// 	c = -1;
// 	if (arena[index] > 16 || arena[index] < 1)
// 		return (-1);
// 	if (!op_tab[arena[index] - 1].coding_byte)
// 		return (1);
// 	else
// 	{
// 		bit = ft_char_to_bit((int)arena[index + 1]);
// 		while (++c < op_tab[arena[index + 1]].nb_arg)
// 		{

// 		}
// 	}
// }

void 	execute_action(t_vm *vm, t_process *process, int size)
{
	if (vm->arena[process->index] == 1)
	{
		vm->nlive++;
		process->nlive++;
	}
	process->index += size;
}

int 	READ_ARENA(t_vm *vm, t_process *process)
{
	int size = 0;

	size = validate_codingbyte(vm->arena[process->index], vm->arena[process->index + 1]);
	if ((vm->arena[process->index] > 16 || vm->arena[process->index] < 1) || size == 0)
	{
		process->index++;
		return (-1);
	}
	else
	{
		if (process->c_to_wait > 0)
			return (0);
		else
		{
			execute_action(vm, process, size);
			return (1);
		}
	}
}

int 	FT_TIME_FOR_CHECKS(t_vm *vm)
{
	t_process	*current;
	t_process	*tmp;

	current = vm->process;
	if ((++vm->checks == MAX_CHECKS) || (vm->nlive >= NBR_LIVE))
	{
		vm->cycle_to_die -= CYCLE_DELTA;
		vm->checks = 0;
	}
	while (current && current->nlive == 0)
	{
		tmp = current;
		current = current->next;
		vm->process = current;
		free(tmp);
		tmp = NULL;
	}
	while (current->next)
	{
		if (current->next->nlive == 0)
		{
			tmp = current->next;
			current->next = current->next->next;
			free(tmp);
			tmp = NULL;
		}
		else
			current->next->nlive = 0;
		current = current->next;
	}
	vm->cycle = vm->cycle_to_die;
	if (!vm->process)
		return (-1);
	return (1);
}

int 	HANDLE_CYCLE(t_vm *vm)
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
	return (vm->cycle > 0);
}

void 	init_cycles(t_vm *vm, t_process *process)
{
	if ((vm->arena[process->index] > 16 || vm->arena[process->index] < 1) ||
		!validate_codingbyte(vm->arena[process->index], vm->arena[process->index + 1]))
		process->c_to_wait = 0;
	else
		process->c_to_wait = op_tab[vm->arena[process->index] - 1].nb_cycle;
}

void	start_vm(t_vm *vm)
{
	t_process	*current;

	while (1)
	{
		current = vm->process;
		while (current)
		{
			if (READ_ARENA(vm, current) != 0)
				init_cycles(vm, current);
			current = current->next;
		}
		output_arena(vm);
		if (getch() == 127)
			break ;
		if (!HANDLE_CYCLE(vm))
			if (!FT_TIME_FOR_CHECKS(vm))
				break ;
		get_vm(NULL, vm);
	}
}