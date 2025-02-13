/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 14:08:59 by mrandou           #+#    #+#             */
/*   Updated: 2020/02/10 17:54:54 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	signal_init(void)
{
	signal(SIGWINCH, signal_window);
	signal(SIGTSTP, signal_stop);
	signal(SIGCONT, signal_cont);
	signal(SIGINT, signal_exit);
	signal(SIGTERM, signal_exit);
	signal(SIGQUIT, signal_exit);
}

void	signal_window(int signum)
{
	t_select *tmp;

	if (signum == SIGWINCH)
	{
		tmp = get_struct(NULL);
		if (!tmp)
			return ;
		display_list(tmp);
	}
}

void	signal_stop(int signum)
{
	t_select	*tmp;
	char		control[2];

	if (signum == SIGTSTP)
	{
		tmp = get_struct(NULL);
		if (!tmp)
			return ;
		exit_reset_attribute(tmp);
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
			return ;
		init_set_attribute(tmp);
		signal(SIGTSTP, signal_stop);
		display_list(tmp);
	}
}

void	signal_exit(int signum)
{
	if (signum == SIGTERM || signum == SIGINT || signum == SIGQUIT)
		exit_shutdown(SUCCESS);
}
