/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_set_attribute.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 18:14:29 by mrandou           #+#    #+#             */
/*   Updated: 2020/01/27 17:47:06 by mrandou          ###   ########.fr       */
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
	s_set.c_lflag &= ~(ICANON | ECHO | ISIG);
	ft_putstr_fd(ALTSCREEN_ON, fd);
	if (tcsetattr(fd, 0, &s_set))
		return (ERROR);
	return (fd);
}

int	init_reset_attribute(struct termios backup, int fd)
{
	ft_putstr_fd(ALTSCREEN_OFF, fd);
	close(fd);
	if (tcsetattr(STDIN_FILENO, 0, &backup))
		return (FAILURE);
	return (SUCCESS);
}
