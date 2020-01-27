/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 14:49:31 by mrandou           #+#    #+#             */
/*   Updated: 2020/01/27 17:29:15 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

void	print_list(char **list, int fd)
{
	int i;

	i = 1;
	while (list[i])
	{
		ft_putstr_fd(list[i++], fd);
		ft_putchar_fd(' ', fd);
	}
}
