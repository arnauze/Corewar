#include "term.h"

// void		signal_handler(int sig)
// {
// 	if (sig == SIGINT || sig == SIGABRT || sig == SIGKILL
// 		|| sig == SIGQUIT || sig == SIGTSTP)
// 		ft_quit(0);
// 	else if (sig == SIGWINCH)
// 	{
// 		tputs(tgetstr("cl", NULL), 0, ft_putint);
// 		if (get_size() == -1)
// 			ft_putstr("Not enough space\n");
// 		else
// 			print_list(g_terminal);
// 	}
// }
