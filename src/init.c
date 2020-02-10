/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 18:14:29 by mrandou           #+#    #+#             */
/*   Updated: 2020/02/10 17:58:11 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int	init_set_attribute(t_select *slt_struct)
{
	struct termios	s_set;

	if (tcgetattr(STDIN_FILENO, &s_set))
		return (ERROR);
	if ((slt_struct->fd = open(ttyname(STDIN_FILENO), O_RDWR)) == ERROR)
		return (ERROR);
	slt_struct->backup = s_set;
	s_set.c_lflag &= ~(ICANON | ECHO);
	if (tcsetattr(slt_struct->fd, 0, &s_set))
		return (ERROR);
	ft_putstr_fd(CUR_OFF, slt_struct->fd);
	ft_putstr_fd(ALTSCREEN_ON, slt_struct->fd);
	put_termcap(TC_CLEAR, 1);
	return (SUCCESS);
}

int	init_termcap(void)
{
	char	*term;

	if (!(term = getenv("TERM")))
	{
		if (tgetent(NULL, DEFAULT_TERM) < 1)
			return (FAILURE);
	}
	else if (tgetent(NULL, term) < 1)
		return (FAILURE);
	return (SUCCESS);
}
