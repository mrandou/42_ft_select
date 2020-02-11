/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 14:49:31 by mrandou           #+#    #+#             */
/*   Updated: 2020/02/11 12:05:40 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	print_select(t_select *slt_struct, int col)
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
		print_str(slt_struct, NULL, col);
}

void	print_colors_type(t_select *slt_struct)
{
	int fd;

	fd = slt_struct->fd;
	if (slt_struct->colors)
	{
		slt_struct->arg_list->type & S_IEXEC ? ft_putstr_fd(CLR_RED, fd) : NULL;
		S_ISDIR(slt_struct->arg_list->type) ? ft_putstr_fd(CLR_CYAN, fd) : NULL;
		S_ISREG(slt_struct->arg_list->type) ? ft_putstr_fd(CLR_BOLD, fd) : NULL;
		S_ISCHR(slt_struct->arg_list->type) ? ft_putstr_fd(CLR_GREEN, fd) : NULL;
		S_ISLNK(slt_struct->arg_list->type) ? ft_putstr_fd(CLR_MAGENTA, fd) : NULL;
	}
}

void	print_str(t_select *slt_struct, char *type, int col)
{
	int	spaces;
	int	len;

	spaces = 0;
	len = ft_strlen(slt_struct->arg_list->content);
	if (len > 29)
		len = 32;
	print_colors_type(slt_struct);
	if (type)
		ft_putstr_fd(type, slt_struct->fd);
	ft_putmstr_fd(slt_struct->arg_list->content, slt_struct->fd, 29);
	if (len == 32)
		ft_putstr_fd("...", slt_struct->fd);
	ft_putstr_fd(TCA_OFF, slt_struct->fd);
	if (col)
	{
		spaces = slt_struct->max_len - len + 1;
		while (spaces--)
			ft_putchar_fd(' ', slt_struct->fd);
	}
	if (!col && slt_struct->arg_list->id
		< slt_struct->max - slt_struct->nb_delete)
		ft_putchar_fd('\n', slt_struct->fd);
}

int		print_by_id(t_select *slt_struct, int id)
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
