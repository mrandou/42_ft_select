/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 14:08:59 by mrandou           #+#    #+#             */
/*   Updated: 2020/02/04 14:10:36 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

void	signal_init()
{
	signal(SIGWINCH, signal_window);
}

void	signal_window(int signum)
{
	t_select *tmp;

	if (signum == SIGWINCH)
	{
		tmp = get_struct(NULL);;
		if (!tmp)
			return;
		print_list(tmp);
	}
}
