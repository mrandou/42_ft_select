/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 14:06:32 by mrandou           #+#    #+#             */
/*   Updated: 2020/01/27 17:36:05 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

int		check_error(int value)
{
	if (value == ER_READ)
		ft_putendl_fd("ft_select: READ Error", 2);
	if (value == ER_EXEC)
		ft_putendl_fd("ft_select: EXECUTION Error", 2);
	if (value == ER_INIT)
		ft_putendl_fd("ft_select: INITIALIZATION Error", 2);
	if (value == ER_RESET)
		ft_putendl_fd("ft_select: RESET Error", 2);
	return (value);
}
