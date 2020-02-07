/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 14:49:31 by mrandou           #+#    #+#             */
/*   Updated: 2020/02/07 16:34:42 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

int			print_by_id(t_select *slt_struct, int id)
{
	t_arglist	*tmp;

	tmp = slt_struct->arg_list;
	slt_struct->arg_list = slt_struct->head;
	while (slt_struct->arg_list)
	{
		if (slt_struct->arg_list->id == id)
		{
			print_select(slt_struct, 1);
			ft_putchar_fd(' ', slt_struct->fd);
			slt_struct->arg_list = tmp;
			return (SUCCESS);
		}
		slt_struct->arg_list = slt_struct->arg_list->next;
	}
	slt_struct->arg_list = tmp;
	return (FAILURE);
}

int			print_column(t_select *slt_struct)
{
	int				id;

	id = 0;
	ioctl(0, TIOCGWINSZ, &slt_struct->window);
	if ((((slt_struct->max - slt_struct->nb_delete) / slt_struct->window.ws_row)
	 + 1) * (slt_struct->max_len + 3) > slt_struct->window.ws_col)
	{
		ft_putstr_fd("Window size is too small", slt_struct->fd);
		return (1);
	}
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

void		print_list(t_select *slt_struct)
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

static int	print_char(int c)
{
	if (!c)
		return (ERROR);
	ft_putchar_fd(c, 0);
	return (c);
}

int			print_termcap(char *str, int nb)
{
	char	*termc;
	int		i;

	i = 0;
	termc = tgetstr(str, NULL);
	if (!termc)
		return (FAILURE);
	while (i < nb)
	{
		if (tputs(termc, 1, print_char))
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

void		print_select(t_select *slt_struct, int col)
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

void	print_str(t_select *slt_struct, char *type, int col)
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
