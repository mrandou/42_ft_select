/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edition.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 11:50:19 by mrandou           #+#    #+#             */
/*   Updated: 2020/01/27 17:46:21 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

int line_edition_read(int fd)
{
	char	buff[4];

	ft_bzero(buff, 4);
	if (read(fd, buff, 4) == ERROR)
		return (ER_READ);
	if (line_edition_execute(line_edition_check(buff)))
		return (ER_EXEC);
	return (SUCCESS);
}

int	line_edition_check(char buff[])
{
	if (!ft_strcmp(buff, TC_UP))
		return (UP);
	else if (!ft_strcmp(buff, TC_DOWN))
		return (DOWN);
	else if (!ft_strcmp(buff, TC_RIGHT))
		return (RIGHT);
	else if (!ft_strcmp(buff, TC_LEFT))
		return (LEFT);
	else if (!ft_strcmp(buff, TC_DEL))
		return (DEL);
	else if (buff[0] == TC_BACKSPACE)
		return (BACKSPACE);
	else if (buff[0] == TC_ESCAPE && !buff[1])
		return (ESCAPE);
	else if (buff[0] == TC_SPACE)
		return (SPACE);
	else if (buff[0] == TC_RETURN)
		return (RETURN);
	return (UNKNOWN);
}

int	line_edition_execute(int action)
{
	if (action == ESCAPE)
		return (ESCAPE);
	return (SUCCESS);
}
