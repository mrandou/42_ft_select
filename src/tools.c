/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 11:24:30 by mrandou           #+#    #+#             */
/*   Updated: 2020/02/10 11:55:50 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void		put_selection(t_select *slt_struct)
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
}

t_select	*get_struct(t_select *slt_struct)
{
	static t_select *data_struct;

	if (slt_struct)
		data_struct = slt_struct;
	else
		return (data_struct);
	return (NULL);
}

int			print_char(int c)
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
