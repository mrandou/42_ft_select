/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 14:49:31 by mrandou           #+#    #+#             */
/*   Updated: 2020/02/10 13:34:17 by mrandou          ###   ########.fr       */
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
		ft_putstr_fd("Window size is too small", slt_struct->fd);
		return (FAILURE);
	}
	return (SUCCESS);
}

int				print_column(t_select *slt_struct)
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

void			print_list(t_select *slt_struct)
{
	print_termcap(TC_CLEAR, 1);
	slt_struct->arg_list = slt_struct->head;
	if (print_column(slt_struct))
	{
		list_set_current_pos(slt_struct);
		return ;
	}
	while (slt_struct->arg_list)
	{
		print_select(slt_struct, 0);
		slt_struct->arg_list = slt_struct->arg_list->next;
	}
	list_set_current_pos(slt_struct);
}

void			print_select(t_select *slt_struct, int col)
{
	int	fd;

	fd = slt_struct->fd;
	if (slt_struct->current == slt_struct->arg_list->id)
	{
		if (slt_struct->arg_list->selected)
			print_str(slt_struct, TCA_SELECT_UNDER, col);
		else
			print_str(slt_struct, TCA_UNDERLINED, col);
	}
	else if (slt_struct->arg_list->selected
		&& !slt_struct->arg_list->deleted)
		print_str(slt_struct, TCA_SELECT, col);
	else if (!slt_struct->arg_list->deleted)
	{
		if (!col && slt_struct->arg_list->id
		< slt_struct->max - slt_struct->nb_delete)
			ft_putendl_fd(slt_struct->arg_list->content, fd);
		else if (!col)
			ft_putstr_fd(slt_struct->arg_list->content, fd);
		else
			print_str(slt_struct, NULL, col);
	}
}

void			print_str(t_select *slt_struct, char *type, int col)
{
	int	spaces;

	spaces = 0;
	if (type)
		ft_putstr_fd(type, slt_struct->fd);
	ft_putstr_fd(slt_struct->arg_list->content, slt_struct->fd);
	ft_putstr_fd(TCA_OFF, slt_struct->fd);
	if (col)
	{
		spaces = slt_struct->max_len
		- ft_strlen(slt_struct->arg_list->content) + 1;
		while (spaces--)
			ft_putchar_fd(' ', slt_struct->fd);
	}
	if (!col && slt_struct->arg_list->id
		< slt_struct->max - slt_struct->nb_delete)
		ft_putchar_fd('\n', slt_struct->fd);
}
