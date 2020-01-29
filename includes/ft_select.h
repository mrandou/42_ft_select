/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 15:09:05 by mrandou           #+#    #+#             */
/*   Updated: 2020/01/29 11:45:03 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FT_SELECT_H
# define __FT_SELECT_H

# include "../libft/incs/libft.h"
# include <termios.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <curses.h>
# include <term.h>

# define SUCCESS	0
# define FAILURE	1
# define ERROR		-1

# define TCA_UP				"\033[A"
# define TCA_DOWN			"\033[B"
# define TCA_RIGHT			"\033[C"
# define TCA_LEFT			"\033[D"
# define TCA_DEL			"\033[3~"
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

# define DEFAULT_TERM		"xterm-256color"

typedef	enum		e_termnum
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
	UNKNOWN
}					t_termnum;

typedef	enum		e_error
{
	ER_READ = 100,
	ER_EXEC,
	ER_INIT,
	ER_RESET,
	ER_NOTERM,
	ER_LIST
}					t_error;

typedef	struct		s_arglist
{
	char				*content;
	int					id;
	int					selected;
	int					deleted;
	struct s_arglist	*next;
	struct s_arglist	*prev;
}					t_arglist;

typedef struct		s_select
{
	t_arglist	*arg_list;
	t_arglist	*head;
	t_arglist	*tail;
	int			fd;
	int			current;
	int			max;
	int			nb_delete;
}					t_select;

int		ft_select(struct s_select *slt_struct);

int		init_set_attribute(struct termios *backup);
int		init_reset_attribute(struct termios backup, int fd);
int		init_termcap();

int		line_read(struct s_select *slt_struct);
int		line_check(char buff[]);

int		exec_main(struct s_select *slt_struct, int action);
void	exec_motion_right(struct s_select *slt_struct);
void	exec_motion_left(struct s_select *slt_struct);

int		check_error(int value);

void	print_list(struct s_select *slt_struct);
int		print_termcap(char *str, int nb);
void	print_str(char *str, char *type, int fd);

int		list_create(struct s_select *slt_struct, char **arg);
int		list_push(struct s_arglist **arglist, char *content);
void	list_free(struct s_arglist *arglist);
void	list_set_current_pos(t_select *slt_struct);

#endif
