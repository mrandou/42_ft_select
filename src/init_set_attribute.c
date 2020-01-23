/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_set_attribute.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 18:14:29 by mrandou           #+#    #+#             */
/*   Updated: 2020/01/23 18:34:00 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

int	init_set_attribute(struct termios *backup)
{
	struct termios	s_set;

	if (tcgetattr(STDIN_FILENO, &s_set))
		return (FAILURE);
	*backup = s_set;
	s_set.c_lflag &= ~(ICANON | ECHO | ISIG);
	if (tcsetattr(STDIN_FILENO, 0, &s_set))
		return (FAILURE);
	return (SUCCESS);
}

int	init_reset_attribute(struct termios backup)
{
	if (tcsetattr(STDIN_FILENO, 0, &backup))
		return (FAILURE);
	return (SUCCESS);
}
