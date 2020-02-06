/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 14:08:59 by mrandou           #+#    #+#             */
/*   Updated: 2020/02/06 17:08:07 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

void	signal_init()
{
	signal(SIGWINCH, signal_window);
	signal(SIGTSTP, signal_tstp);
	signal(SIGCONT, signal_cont);
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

void	signal_tstp(int signum)
{
	t_select	*tmp;
	char		control[2];

	if (signum == SIGTSTP)
	{
		tmp = get_struct(NULL);;
		if (!tmp)
			return;
		init_reset_attribute(tmp);
		get_struct(tmp);
		control[0] = tmp->backup.c_cc[VSUSP];
		control[1] = 0;
		signal(SIGTSTP, SIG_DFL);
		ioctl(0, TIOCSTI, control);
	}
}

void	signal_cont(int signum)
{
	t_select *tmp;

	if (signum == SIGCONT)
	{
		tmp = get_struct(NULL);
		if (!tmp)
			return;
		init_set_attribute(&tmp->backup);
		get_struct(tmp);
		signal(SIGTSTP, signal_tstp);
		print_list(tmp);
	}
}
