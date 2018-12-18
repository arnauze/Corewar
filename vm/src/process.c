/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 14:42:33 by amagnan           #+#    #+#             */
/*   Updated: 2018/12/16 14:42:34 by amagnan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/vm.h"

t_process			*make_node(int id)
{
	t_process		*process;
	int				i;

	i = -1;
	process = (t_process *)malloc(sizeof(t_process));
	while (++i <= 16)
		ft_bzero(process->r[i], 5);
	process->id = id;
	process->c_to_wait = 0;
	process->nlive = 0;
	process->index = 0;
	process->carry = 0;
	process->next = NULL;
	return (process);
}

void				add_node(t_process *head, t_process *copy)
{
	t_process		*current;
	int 			i;

	i = -1;
	current = head;
	while (current && current->next)
		current = current->next;
	current->next = make_node(current->id + 1);
	current = current->next;
	while (++i < 16)
		ft_strcpy(current->r[i], copy->r[i]);
}

void				delete_node(t_process *head, int id)
{
	t_process		*current;
	t_process		*tmp;

	current = head;
	while (current && current->next && current->next->id != id)
		current = current->next;
	tmp = current->next;
	if (current->next)
	{
		current->next = current->next->next;
		free(tmp);
	}
}
