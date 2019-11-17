/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Arnaud <Arnaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 23:10:01 by amagnan           #+#    #+#             */
/*   Updated: 2019/03/13 23:16:10 by feedme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "../../libft/libft.h"
# include "../op/op.h"

# include <ncurses.h>
# include <time.h>

typedef struct			s_header
{
	unsigned int		magic;
	char				prog_name[PROG_NAME_LENGTH + 1];
	unsigned int		prog_size;
	char				comment[COMMENT_LENGTH + 1];
}						t_header;

typedef struct			s_process
{
	int					id;
	int					c_to_wait;
	unsigned char		**r;
	int					nlive;
	unsigned int		index;
	int					carry;
	int					flag;
	struct s_process	*next;
}						t_process;

typedef struct			s_player
{
	t_header			header;
	int					talk;
	int					nlive;
	int					fd;
	unsigned char		*nbr;
	int					last_live;
	unsigned char		*filename;
}						t_player;

typedef struct			s_vm
{
	t_player			*p1;
	t_player			*p2;
	t_process			*process;
	unsigned char		*arena;
	int					cycle_to_die;
	int					tcycle;
	int					cycle;
	int					checks;
	int					nlive;
	int					nbr_cycles;
}						t_vm;

typedef struct			s_op
{
	char				*command;
	int					nb_arg;
	int					arg_type[3];
	int					op_code;
	int					nb_cycle;
	char				*lcommand;
	char				coding_byte;
	char				size;
}						t_op;

t_op					g_op_tab[19];
typedef void			(*t_fcts)(t_process*, unsigned char*);

void					free_all(t_vm *vm);
unsigned char			*ft_read_files(char **argv, t_vm *vm);
int						ft_get_player(t_player *p, unsigned char *arena);
t_process				*make_node(int id);
void					add_node(int index, t_process *head, t_process *copy);
void					start_vm(t_vm *vm);
t_vm					get_vm(char **argv, t_vm *new);
void					initialize_process(t_vm *vm);
void					output_arena(t_vm *vm);

void					live(t_process *pl, unsigned char *arena, t_vm *vm);
void					load(t_process *pl, unsigned char *arena);
void					store(t_process *pl, unsigned char *arena);
void					add(t_process *pl, unsigned char *arena);
void					sub(t_process *pl, unsigned char *arena);
void					and(t_process *pl, unsigned char *arena);
void					or(t_process *pl, unsigned char *arena);
void					xor(t_process *pl, unsigned char *arena);
void					zjump(t_process *pl, unsigned char *arena);
void					ldi(t_process *pl, unsigned char *arena);
void					sti(t_process *pl, unsigned char *arena);
void					forki(t_process *pl, unsigned char *arena);
void					aff(t_process *pl, unsigned char *arena);
void					lld(t_process *pl, unsigned char *arena);
void					lldi(t_process *pl, unsigned char *arena);
void					lfork(t_process *pl, unsigned char *arena);
void					swap(t_process *pl, unsigned char *arena);
void					wipe(t_process *pl, unsigned char *arena);

void					set_last_alive(t_vm *vm, char *tmp);
char					*cw_strsub(unsigned char *arena, int i, int size);
char					*char_to_bit(unsigned char c);
void					fill_regis(unsigned char *reg, char *bits);
char					*int_to_bit(int c);
char					*get_dir(int i, unsigned char *arena);
int						ft_powof2(int pow);
int						bit_to_dec(char *str, int size);
int						get_ind(int i, unsigned char *arena, int size);
int						get_regis(unsigned char *arena, int i);
int						validate_codingbyte(unsigned char op_code,
unsigned char c_byte);
int						get_arg3_pos(unsigned char code);
int						get_arg3i_pos(unsigned char code);
int						get_nb(int i, unsigned char *arena,
unsigned char code, t_process *pl);
int						get_lnb(int i, unsigned char *arena,
unsigned char code, t_process *pl);
int						get_arg2_pos(unsigned char code);
int						get_arg2i_pos(unsigned char code);
void					free_all(t_vm *vm);
void					free_all2(t_vm *vm);
void					helper(void);
void					helper2(t_vm *vm, unsigned int *i);
void					helper3(t_vm *vm, unsigned int *i);
int						is_process_index(unsigned int i, t_process *head);
void					add_end_string(int x, int i);
void					initialize_players(t_player *p1, t_player *p2);
int						c_byte_size(unsigned char c_byte);
int						validate_helper(unsigned char op_code,
unsigned char c_byte);
void					free_process(t_process **proc);
int						validate_codingbyte(unsigned char op_code,
unsigned char c_byte);
void					init_cycles(t_vm *vm, t_process *process);
int						handle_cycle(t_vm *vm);
void					checks_helper(t_process *current);
int						ft_time_for_checks(t_vm *vm);

#endif
