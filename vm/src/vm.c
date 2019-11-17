/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 14:03:55 by amagnan           #+#    #+#             */
/*   Updated: 2019/03/15 14:25:52 by feedme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/vm.h"

t_vm	get_vm(char **argv, t_vm *new)
{
	static t_vm vm;

	if (argv && !new)
	{
		if (!(vm.p1 = (t_player*)malloc(sizeof(t_player))) ||
		!(vm.p2 = (t_player*)malloc(sizeof(t_player))))
			exit(-1);
		vm.process = NULL;
		vm.nbr_cycles = -5;
		vm.arena = ft_read_files(argv, &vm);
		vm.cycle_to_die = CYCLE_TO_DIE;
		vm.tcycle = 0;
		vm.cycle = vm.cycle_to_die;
		vm.checks = 0;
		vm.nlive = 0;
		initialize_process(&vm);
	}
	else
	{
		if (new)
			vm = *new;
	}
	return (vm);
}

void	execute_action(t_vm *vm, t_process *process, int size)
{
	t_fcts		tab[18];

	tab[1] = &load;
	tab[2] = &store;
	tab[3] = &add;
	tab[4] = &sub;
	tab[5] = &and;
	tab[6] = &or;
	tab[7] = &xor;
	tab[8] = &zjump;
	tab[9] = &ldi;
	tab[10] = &sti;
	tab[11] = &forki;
	tab[12] = &lld;
	tab[13] = &lldi;
	tab[14] = &lfork;
	tab[15] = &aff;
	tab[16] = &swap;
	tab[17] = &wipe;
	if (vm->arena[process->index] == 1)
		live(process, vm->arena, vm);
	else
		tab[vm->arena[process->index] - 1](process, vm->arena);
	process->index = (process->index + size) % MEM_SIZE;
}

int		read_arena(t_vm *vm, t_process *process)
{
	int			size;

	size = validate_codingbyte(vm->arena[process->index],
	vm->arena[(process->index + 1) % MEM_SIZE]);
	if ((vm->arena[process->index] > 18 ||
	vm->arena[process->index] < 1) || size == 0)
	{
		process->index = (process->index + 1) % MEM_SIZE;
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

void	dump_mem(t_vm *vm)
{
	int		i;
	char	*tmp;

	i = -1;
	endwin();
	while (++i < MEM_SIZE)
	{
		tmp = ft_itoa_base(vm->arena[i], 16, "0123456789abcdef");
		if (ft_strlen(tmp) < 2)
			ft_putchar('0');
		ft_putstr(tmp);
		ft_putchar(' ');
		free(tmp);
		if ((i + 1) % 32 == 0)
			write(1, "\n", 1);
	}
	free_all(vm);
	exit(0);
}

void	start_vm(t_vm *vm)
{
	t_process	*current;

	while (1)
	{
		if (!(vm->nbr_cycles))
			dump_mem(vm);
		current = vm->process;
		while (current)
		{
			if (read_arena(vm, current))
				init_cycles(vm, current);
			current = current->next;
		}
		if (getch() == 127)
			break ;
		output_arena(vm);
		if (!handle_cycle(vm))
			if (ft_time_for_checks(vm))
				break ;
	}
}
