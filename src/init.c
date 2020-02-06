/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 18:14:29 by mrandou           #+#    #+#             */
/*   Updated: 2020/02/06 14:16:35 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

int	init_set_attribute(struct termios *backup)
{
	struct termios	s_set;
	int				fd;

	if (tcgetattr(STDIN_FILENO, &s_set))
		return (ERROR);
	if ((fd = open(ttyname(STDIN_FILENO), O_RDWR)) == ERROR)
		return (ERROR);
	*backup = s_set;
	s_set.c_lflag &= ~(ICANON | ECHO);
	ft_putstr_fd(ALTSCREEN_ON, fd);
	ft_putstr_fd(CUR_OFF, fd);
	if (tcsetattr(fd, 0, &s_set))
		return (ERROR);
	print_termcap(TC_CLEAR, 1);
	return (fd);
}

int	init_reset_attribute(t_select *slt_struct)
{
	ft_putstr_fd(CUR_ON, slt_struct->fd);
	ft_putstr_fd(ALTSCREEN_OFF, slt_struct->fd);
	close(slt_struct->fd);
	if (tcsetattr(STDIN_FILENO, 0, &slt_struct->backup))
		return (FAILURE);
	return (SUCCESS);
}

int	init_termcap()
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
