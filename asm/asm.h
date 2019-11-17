/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 20:37:40 by ghdesfos          #+#    #+#             */
/*   Updated: 2019/03/13 22:44:45 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# include "op.h"
# include "get_next_line.h"

typedef struct s_ins	t_ins;

struct					s_ins
{
	char	*label;
	int		ins_code;
	char	*par1;
	char	*par2;
	char	*par3;
	int		length;
	int		n;
	t_ins	*next;
};

typedef struct s_fd		t_fd;

struct					s_fd
{
	int		fd1;
	int		fd2;
	int		fd3;
	int		fd4;
	int		fd5;
};

typedef struct s_champ	t_champ;

struct					s_champ
{
	char	*name;
	char	*comment;
	t_ins	*ins;
	char	*strtofree;
};

int						find_next_opening_quote_sign(int fd);
int						find_next_closing_quote_sign(int fd);
void					check_four_valid_quote_signs(t_champ *champ, \
						t_fd *sfd, char *path);
void					close_fd(t_fd *sfd);

void					regularize_name(t_champ *champ, char *str);
void					get_name_champion(t_champ *champ, int fd);
void					regularize_comment(t_champ *champ, char *str);
void					get_comment_champion(t_champ *champ, int fd);
void					get_name_and_comment_champion(t_champ *champ, \
						t_fd *std, char *path);

void					move_to_first_instruction(int fd);
t_ins					*add_ins_node_to_list(t_champ *champ, int n);
char					*add_label_to_node(t_ins *ins, char *str);
void					put_instructions_and_labels_into_list(t_champ *champ, \
						int fd);
void					get_instructions_list(t_champ *champ, t_fd *std, \
						char *path);

int						check_valid_ins_sub(t_ins *ins);
int						check_valid_ins_sub2(t_ins *ins);
int						check_valid_ins_sub3(t_ins *ins);
int						check_valid_ins(t_ins *ins, int val, int val2, \
						int val3);
void					check_validity_instructions(t_champ *champ);

int						check_valid_param(char *param, int reg, int dir, \
						int ind);

void					add_op_nb_to_node_sub_sub(t_ins *ins, char *op);
void					add_op_nb_to_node_sub(t_ins *ins, char *op);
char					*add_op_nb_to_node(t_champ *champ, t_ins *ins, \
						char *str);
char					*add_param_to_node(t_champ *champ, t_ins *ins, \
						int param_nb, char *str);
void					add_ins_to_node(t_champ *champ, t_ins *ins, char *str);

int						get_size_coding_byte(t_ins *ins);
int						get_size_register_parameters(t_ins *ins);
int						get_size_direct_parameters(t_ins *ins);
int						get_size_indirect_parameters(t_ins *ins);
void					compute_ins_length(t_champ *champ);

void					get_distance_node_to_label_error_management(t_champ \
						*champ, char *label, int error_nb);
int						get_distance_node_to_label(t_champ *champ, \
						t_ins *head, int node_nb, char *label);
void					convert_label_to_dist_ins(t_champ *champ, t_ins *head, \
						t_ins *ins, char **par);
void					compute_ins_distance_label(t_champ *champ);

char					*convert_file_name(char *file_name);
void					add_magic_code(int fd);
void					add_champion_name(t_champ *champ, int fd);
void					add_champion_comment(t_champ *champ, int fd);
void					create_output_file(t_champ *champ, char *file_name);

int						compute_length_champion(t_champ *champ);
void					add_champion_length_to_output_file(t_champ *champ, \
						int fd);

char					determine_computer_little_or_big_endian(void);
void					add_ins_parameters_one_byte_long(int fd, int i);
void					add_ins_parameters_two_bytes_long(int fd, int i, \
						char endian);
void					add_ins_parameters_four_bytes_long(int fd, int i, \
						char endian);
void					add_ins_parameters_to_champion_code(int ins_code, \
						char *par, int fd);

void					add_ins_code(t_ins *ins, int fd);
void					add_coding_byte(t_ins *ins, int fd);
void					add_champion_code_to_output_file(t_champ *champ, \
						int fd);

int						check_valid_number_format_in_param(char *param);
int						check_and_skip_name_or_comment_section(int fd, \
						char *line);
void					check_no_elements_before_end_name_and_comment(t_champ \
						*champ, t_fd *std, char *path);
void					check_wrong_element_before_value(t_champ *champ, \
						char *str, int len);
void					check_wrong_element_after_value(t_champ *champ, \
						char *str, int len);

int						check_format_input_file(char *file_name);

int						ft_strlen(char *str);
char					*ft_strdup(char *str);
char					*ft_trim_begin(char *str);
int						ft_strchr_nb(char *str, char c);
void					ft_putchar_fd(char c, int fd);
void					ft_putstr_fd(char *str, int fd);
char					*ft_concat_strings(char *s1, char *s2, int freed);
void					ft_syntax_error(char *str, t_champ *champ);
int						ft_check_not_empty_line(char *str);
char					*ft_strdup_nb(char *str, int max);
int						ft_strcmp(char *s1, char *s2);
int						ft_strcmp_nb(char *s1, char *s2, int max);
void					ft_putnbr_fd(int n, int fd);
void					itoa_isnegative(int *n, int *negative);
char					*ft_itoa(int n);
int						avoid_int_overflow_atoi(long number, int sign);
int						ft_atoi(char *str);
void					free_ins_node(t_ins *ins);
void					free_champ_node(t_champ *champ);
char					*ft_concat_one_char_and_one_string(char c, char *s2);
void					print_t_champ(t_champ *champ);
void					initialize_champ_list(t_champ *champ);
int						ft_min(int a, int b, int c);

#endif
