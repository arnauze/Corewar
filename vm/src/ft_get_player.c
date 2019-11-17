/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 14:00:39 by amagnan           #+#    #+#             */
/*   Updated: 2019/03/13 23:12:32 by feedme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/vm.h"

static void	get_magic_header(int fd, t_player *p)
{
	char	buf[5];

	if (read(fd, buf, 4) > 0)
		p->header.magic = (unsigned int)ft_hex_to_decimal("ea83f3");
}

static int	get_name_and_size(int fd, t_player *p)
{
	unsigned char	buf[5];

	if (read(fd, p->header.prog_name, PROG_NAME_LENGTH))
		p->header.prog_name[PROG_NAME_LENGTH] = '\0';
	read(fd, buf, 4);
	ft_bzero(buf, ft_strlen((char*)buf));
	if (read(fd, buf, 4))
	{
		buf[4] = '\0';
		p->header.prog_size = get_ind(0, buf, 4);
		if (p->header.prog_size > CHAMP_MAX_SIZE || !p->header.prog_size)
			return (0);
	}
	return (42);
}

static void	get_comment(int fd, t_player *p)
{
	char	trash[4];

	if (read(fd, p->header.comment, COMMENT_LENGTH))
		p->header.comment[COMMENT_LENGTH] = '\0';
	read(fd, trash, 4);
}

static void	get_executable(int fd, t_player *p, unsigned char *arena)
{
	unsigned int	i;

	if ((i = read(fd, arena, p->header.prog_size)) < p->header.prog_size)
		ft_exit_msg("Couldn't read the executable properly\n");
	while (i < 2048)
		arena[i++] = 0;
}

int			ft_get_player(t_player *p, unsigned char *arena)
{
	get_magic_header(p->fd, p);
	if (!get_name_and_size(p->fd, p))
		return (0);
	get_comment(p->fd, p);
	get_executable(p->fd, p, arena);
	return (1);
}
