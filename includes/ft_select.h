/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 15:09:05 by mrandou           #+#    #+#             */
/*   Updated: 2020/02/11 10:28:49 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FT_SELECT_H
# define __FT_SELECT_H

# include "../libft/incs/libft.h"
# include <termios.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include <curses.h>
# include <term.h>

# define SUCCESS			0
# define FAILURE			1
# define ERROR				-1

# define HEAD				0
# define TAIL				1

# define TCA_UP				"\033[A"
# define TCA_DOWN			"\033[B"
# define TCA_RIGHT			"\033[C"
# define TCA_LEFT			"\033[D"
# define TCA_DEL			"\033[3~"
# define TCA_HOME			"\033[H"
# define TCA_END			"\033[F"
# define TCA_BACKSPACE		'\177'
# define TCA_ESCAPE			'\033'
# define TCA_SPACE			'\040'
# define TCA_RETURN			'\012'
# define TCA_SELECT			"\033[100m"
# define TCA_UNDERLINED		"\033[4m"
# define TCA_SELECT_UNDER	"\033[100m\033[4m"
# define TCA_OFF			"\033[0m"

# define TC_GO_LEFT			"le"
# define TC_GO_RIGHT		"nd"
# define TC_GO_UP			"up"
# define TC_GO_DOWN			"do"
# define TC_GO_BEGIN		"cr"
# define TC_CLEAR			"cl"
# define TC_CLEAR_NEXT		"cd"
# define TC_DELETE_CHAR		"dc"
# define TC_DELETE_LINE		"dl"

# define ALTSCREEN_ON		"\033[?1049h"
# define ALTSCREEN_OFF		"\033[?1049l"
# define CUR_ON				"\033[?25h"
# define CUR_OFF			"\033[?25l"

# define CLR_BOLD			"\033[1m"
# define CLR_RED			"\033[31m"
# define CLR_GREEN			"\033[32m"
# define CLR_MAGENTA		"\033[35m"
# define CLR_CYAN			"\033[36m"

# define DEFAULT_TERM		"xterm-256color"

typedef	enum	e_termnum
{
	UP = 2,
	DOWN,
	LEFT,
	RIGHT,
	SPACE,
	ESCAPE,
	BACKSPACE,
	DEL,
	RETURN,
	TAB,
	HOME,
	END,
	UNKNOWN
}				t_termnum;

typedef	enum	e_error
{
	ER_READ = 100,
	ER_EXEC,
	ER_INIT,
	ER_RESET,
	ER_NOTERM,
	ER_LIST,
	ER_WINDOW
}				t_error;

typedef	enum	e_type
{
	T_REG,
	T_DIR,
	T_CHR,
	T_BLK,
	T_FIFO,
	T_LNK,
	T_SOCK
}				t_type;

typedef	struct	s_arglist
{
	char					*content;
	int						id;
	int						selected;
	int						deleted;
	int						type;
	struct s_arglist		*next;
	struct s_arglist		*prev;
}				t_arglist;

typedef struct	s_select
{
	t_arglist				*arg_list;
	t_arglist				*head;
	t_arglist				*tail;
	struct termios			backup;
	struct winsize			window;
	int						fd;
	int						current;
	int						max;
	int						nb_delete;
	int						max_len;
	int						win_small;
	int						colors;
}				t_select;

int				ft_select(struct s_select *slt_struct);

int				init_set_attribute(struct s_select *slt_struct);
int				init_termcap(void);

int				exit_reset_attribute(struct s_select *slt_struct);
int				exit_check_error(int value);
void			exit_shutdown(int error);
void			exit_list_free(struct s_arglist *arglist);

int				key_read(struct s_select *slt_struct);
int				key_check(char buff[]);

int				exec_main(struct s_select *slt_struct, int action);
void			exec_motion_down(struct s_select *slt_struct);
void			exec_motion_up(struct s_select *slt_struct);
void			exec_motion_lr(t_select *slt_struct, int motion);
int				exec_delete(struct s_select *slt_struct);

int				display_column(struct s_select *slt_struct);
void			display_list(struct s_select *slt_struct);
void			display_selection(struct s_select *slt_struct);

void			print_select(struct s_select *slt_struct, int col);
void			print_colors_type(struct s_select *slt_struct);
void			print_str(struct s_select *slt_struct, char *type, int col);
int				print_by_id(struct s_select *slt_struct, int id);

int				list_create(struct s_select *slt_struct, char **arg);
int				list_push(struct s_arglist **arglist, char *content);
int				list_head_tail(struct s_select *slt_struct, int direction);
int				list_id_position(struct s_select *slt_struct, int id);
int				list_check_type(char *arg);

void			signal_init(void);
void			signal_window(int signum);
void			signal_stop(int signum);
void			signal_cont(int signum);
void			signal_exit(int signum);

t_select		*get_struct(struct s_select *slt_struct);
int				put_char(int c);
int				put_termcap(char *str, int nb);

#endif
