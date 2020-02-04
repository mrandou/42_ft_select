/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 11:50:19 by mrandou           #+#    #+#             */
/*   Updated: 2020/02/04 14:00:22 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

int line_read(struct s_select *slt_struct)
{
	char	buff[5];

	ft_bzero(buff, 5);
	get_struct(slt_struct);
	if (read(slt_struct->fd, buff, 4) == ERROR)
		return (ER_READ);
	return (line_check(buff));
}

int	line_check(char buff[])
{
	if (!ft_strcmp(buff, TCA_UP))
		return (UP);
	else if (!ft_strcmp(buff, TCA_DOWN))
		return (DOWN);
	else if (!ft_strcmp(buff, TCA_RIGHT))
		return (RIGHT);
	else if (!ft_strcmp(buff, TCA_LEFT))
		return (LEFT);
	else if (!ft_strcmp(buff, TCA_DEL))
		return (DEL);
	else if (buff[0] == TCA_BACKSPACE)
		return (BACKSPACE);
	else if (buff[0] == TCA_ESCAPE && !buff[1])
		return (ESCAPE);
	else if (buff[0] == TCA_SPACE)
		return (SPACE);
	else if (buff[0] == TCA_RETURN)
		return (RETURN);
	return (UNKNOWN);
}
