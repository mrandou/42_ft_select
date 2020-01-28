/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 18:14:29 by mrandou           #+#    #+#             */
/*   Updated: 2020/01/28 17:43:37 by mrandou          ###   ########.fr       */
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
	ft_putstr_fd(CUR_OFF, fd);
	if (tcsetattr(fd, 0, &s_set))
		return (ERROR);
	print_termcap(TC_CLEAR, 1);
	return (fd);
}

int	init_reset_attribute(struct termios backup, int fd)
{
	ft_putstr_fd(ALTSCREEN_OFF, fd);
	ft_putstr_fd(CUR_ON, fd);
	close(fd);
	if (tcsetattr(STDIN_FILENO, 0, &backup))
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

int	init_struct(struct s_select *slt_struct, char **arg_list)
{
	slt_struct->nb_delete = 0;
	if (list_create(slt_struct, arg_list))
		return (FAILURE);
	return (SUCCESS);
}
