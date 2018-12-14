#include "term.h"

int		get_size(t_term *term)
{
	ioctl(STDERR_FILENO, TIOCGWINSZ, &term->win_size);
	term->max_col = term->win_size.ws_col;
	term->max_row = term->win_size.ws_row;
	if (term->max_row <= 4096 / 64)
		return (-1);
	return (1);
}
