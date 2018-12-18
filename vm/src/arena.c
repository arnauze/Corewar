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

void			output_arena(t_vm *vm)
{
	unsigned int	i;
	char			*t;

	i = 0;
	tputs(tgetstr("mr", NULL), 0, ft_putint);
	while (i < 2048)
	{
		if (i < vm->p1.header.prog_size)
			tputs(tgetstr("mr", NULL), 0, ft_putint);
		if (IS_PROCESS_INDEX(i, vm->process))
			tputs(tgetstr("me", NULL), 0, ft_putint);
		t = ft_itoa_base(vm->arena[i], 16, "0123456789abcdef");
		if (ft_strlen(t) < 2)
			ft_putchar('0');
		ft_putstr(t);
		if ((i + 1) % 64 == 0)
			ft_putchar('\n');
		else
			ft_putchar(' ');
		i++;
		if (i >= vm->p1.header.prog_size)
			tputs(tgetstr("me", NULL), 0, ft_putint);
	}
	while (i < 4096)
	{
		if (i - 2048 < vm->p2.header.prog_size)
			tputs(tgetstr("mr", NULL), 0, ft_putint);
		if (IS_PROCESS_INDEX(i, vm->process))
			tputs(tgetstr("me", NULL), 0, ft_putint);
		t = ft_itoa_base(vm->arena[i], 16, "0123456789abcdef");
		if (ft_strlen(t) < 2)
			ft_putchar('0');
		ft_putstr(t);
		if ((i + 1) % 64 == 0)
			ft_putchar('\n');
		else
			ft_putchar(' ');
		i++;
		if (i - 2048 >= vm->p2.header.prog_size)
			tputs(tgetstr("me", NULL), 0, ft_putint);
	}
}
