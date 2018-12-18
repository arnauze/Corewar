/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 13:58:34 by amagnan           #+#    #+#             */
/*   Updated: 2018/12/16 13:58:36 by amagnan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/vm.h"

static void			initialize_players(t_player *p1, t_player *p2)
{
	p1->nlive = 0;
	p1->talk = 0;
	p1->fd = 0;
	p2->nlive = 0;
	p2->talk = 0;
	p2->fd = 0;
}

static void			make_process(t_vm *vm)
{
	vm->process = make_node(0);
	vm->process->next = make_node(1);
}

void				initialize_process(t_vm *vm)
{
	vm->process->index = 0;
	vm->process->c_to_wait = op_tab[vm->arena[vm->process->index] - 1].nb_cycle;
	vm->process->next->index = 2048;
	vm->process->next->c_to_wait = op_tab[vm->arena[vm->process->next->index] - 1].nb_cycle;
}

static char			*ft_get_file(char **argv, int x)
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

unsigned char		*ft_read_files(char **argv, t_vm *vm)
{
	unsigned char	*arena;

	initialize_players(&vm->p1, &vm->p2);
	make_process(vm);
	arena = (unsigned char *)ft_strnew(4096);
	if (((vm->p1.fd = open(ft_get_file(argv, 1), O_RDONLY)) < 0)
		|| (vm->p2.fd = open(ft_get_file(argv, 2), O_RDONLY)) < 0)
		ft_exit_msg("File can't be open\n");
	if (!ft_get_player(&vm->p1, arena) || !ft_get_player(&vm->p2, arena + 2048))
		ft_exit_msg("File error\n");
	return (arena);
}
