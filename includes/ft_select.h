/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 15:09:05 by mrandou           #+#    #+#             */
/*   Updated: 2020/01/27 17:42:33 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FT_SELECT_H
# define __FT_SELECT_H

# include "../libft/incs/libft.h"
# include <termios.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# define SUCCESS	0
# define FAILURE	1
# define ERROR		-1

# define TC_UP				"\033[A"
# define TC_DOWN			"\033[B"
# define TC_RIGHT			"\033[C"
# define TC_LEFT			"\033[D"
# define TC_DEL				"\033[3~"
# define TC_BACKSPACE		'\177'
# define TC_ESCAPE			'\033'
# define TC_SPACE			'\040'
# define TC_RETURN			'\012'

# define ALTSCREEN_ON		"\033[?1049h"
# define ALTSCREEN_OFF		"\033[?1049l"

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
	ER_RESET
}					t_error;

int		ft_select(char **arg_list);

int		init_set_attribute(struct termios *backup);
int		init_reset_attribute(struct termios backup, int fd);

int		line_edition_read(int fd);
int		line_edition_check(char buff[]);
int		line_edition_execute(int action);

int		check_error(int value);

void	print_list(char **list, int fd);

#endif
