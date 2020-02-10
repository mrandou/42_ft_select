/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 14:49:31 by mrandou           #+#    #+#             */
/*   Updated: 2020/02/10 18:00:04 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static int		check_window_size(t_select *slt_struct)
{
	if (ioctl(0, TIOCGWINSZ, &slt_struct->window)
	|| slt_struct->window.ws_col <= 0 || slt_struct->window.ws_row <= 0)
		exit_check_error(ER_WINDOW);
	if ((((slt_struct->max - slt_struct->nb_delete) / slt_struct->window.ws_row)
	+ 1) * (slt_struct->max_len + 3) > slt_struct->window.ws_col)
	{
		slt_struct->win_small = 1;
		ft_putstr_fd("Window size is too small", slt_struct->fd);
		return (FAILURE);
	}
	slt_struct->win_small = 0;
	return (SUCCESS);
}

int				display_column(t_select *slt_struct)
{
	int				id;

	id = 0;
	if (check_window_size(slt_struct))
		return (1);
	if ((slt_struct->max - slt_struct->nb_delete) >= slt_struct->window.ws_row)
	{
		while (slt_struct->arg_list
		&& slt_struct->arg_list->id < slt_struct->window.ws_row)
		{
			while (!print_by_id(slt_struct, id))
				id += slt_struct->window.ws_row;
			slt_struct->arg_list = slt_struct->arg_list->next;
			if (slt_struct->arg_list->id < slt_struct->window.ws_row
			&& !slt_struct->arg_list->deleted)
			{
				ft_putchar_fd('\n', slt_struct->fd);
				id = slt_struct->arg_list->id;
			}
		}
		return (1);
	}
	return (0);
}

void			display_list(t_select *slt_struct)
{
	put_termcap(TC_CLEAR, 1);
	slt_struct->arg_list = slt_struct->head;
	if (display_column(slt_struct))
	{
		list_id_position(slt_struct, slt_struct->current);
		return ;
	}
	while (slt_struct->arg_list)
	{
		print_select(slt_struct, 0);
		slt_struct->arg_list = slt_struct->arg_list->next;
	}
	list_id_position(slt_struct, slt_struct->current);
}

void			display_selection(t_select *slt_struct)
{
	int	i;

	i = 0;
	slt_struct->arg_list = slt_struct->head;
	while (slt_struct->arg_list)
	{
		if (!slt_struct->arg_list->deleted && slt_struct->arg_list->selected)
		{
			if (i)
				ft_putchar(' ');
			ft_putstr(slt_struct->arg_list->content);
			i++;
		}
		slt_struct->arg_list = slt_struct->arg_list->next;
	}
	slt_struct->arg_list = slt_struct->head;
	ft_putchar('\n');
}
