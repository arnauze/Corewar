/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 15:10:57 by amagnan           #+#    #+#             */
/*   Updated: 2019/03/15 14:32:29 by feedme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
**	We search for an opening quote as soon as we close one, so we are not \
**	in a comment at this point.
**	We thus should find the first " sign that is not in a comment \
**	(after a COMMENT_CHAR (#) and before the end of the line...)
*/

int		find_next_opening_quote_sign(int fd)
{
	char	c;
	int		comment_flag;

	comment_flag = 0;
	while (read(fd, &c, 1))
	{
		if (c == COMMENT_CHAR)
			comment_flag = 1;
		if (c == '\n')
			comment_flag = 0;
		if (comment_flag == 0 && c == '"')
			return (1);
	}
	return (0);
}

/*
**	A closing quote is the first " sign coming after an opening quote.
*/

int		find_next_closing_quote_sign(int fd)
{
	char c;

	while (read(fd, &c, 1))
	{
		if (c == '"')
			return (1);
	}
	return (0);
}

/*
**	In the function below we check that there are just 4 valid " (quote) signs \
**	in the file. By valid quote signs, we mean those that are not in a comment.
**	Why 4? because there has to be 2 for the .name and 2 for the .comment \
**	declaration. At no other points of the file should there be any other, \
**	except in the comments.
*/

void	check_four_valid_quote_signs(t_champ *champ, t_fd *sfd, char *path)
{
	int		fd;
	int		valid_quotes;
	int		inc;

	if ((fd = open(path, O_RDONLY)) == -1)
		return ;
	valid_quotes = 0;
	inc = 1;
	while (inc != 0)
	{
		inc = 0;
		inc += find_next_opening_quote_sign(fd);
		inc += find_next_closing_quote_sign(fd);
		valid_quotes += inc;
	}
	sfd->fd1 = fd;
	if (valid_quotes != 4)
		ft_syntax_error("the file does not contain 4 \'valid\' quotes", champ);
}

/*
**	We close the fd at the end of their parallel use, as we need to have \
**	some not reused by another function. The reason is that \
**	the get_next_line function keeps in memory some elements linked to \
**	a specific fd that will be reused for the next call \
**	and that should not be used for a different file with a same fd...
*/

void	close_fd(t_fd *sfd)
{
	if (close(sfd->fd1) == -1)
		return ;
	if (close(sfd->fd2) == -1)
		return ;
	if (close(sfd->fd3) == -1)
		return ;
	if (close(sfd->fd4) == -1)
		return ;
	if (close(sfd->fd5) == -1)
		return ;
}

int		main(int argc, char **argv)
{
	t_champ	champ;
	t_fd	sfd;

	if (argc == 2)
	{
		if (check_format_input_file(argv[1]) == 0)
		{
			ft_putstr_fd("File passed to ./asm needs to exist and be .s", 2);
			return (0);
		}
		initialize_champ_list(&champ);
		check_four_valid_quote_signs(&champ, &sfd, argv[1]);
		get_name_and_comment_champion(&champ, &sfd, argv[1]);
		get_instructions_list(&champ, &sfd, argv[1]);
		close_fd(&sfd);
		compute_ins_length(&champ);
		compute_ins_distance_label(&champ);
		check_validity_instructions(&champ);
		create_output_file(&champ, argv[1]);
		free_champ_node(&champ);
		return (1);
	}
	else
		ft_putstr_fd("Usage: ./asm <sourcefile.s>", 2);
	return (0);
}
