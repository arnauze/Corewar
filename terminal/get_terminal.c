#include "term.h"

t_term		get_terminal(void)
{
	t_term	terminal;
	struct termios  termios;
	struct termios  old_termios;

	tgetent(NULL, getenv("TERM"));
	tcgetattr(0, &old_termios);
	tcgetattr(0, &termios);
	terminal.old_term = old_termios;
	terminal.new_term = termios;
	ioctl(STDERR_FILENO, TIOCGWINSZ, &terminal.win_size);
	return (terminal);
}
