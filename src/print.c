/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 14:49:31 by mrandou           #+#    #+#             */
/*   Updated: 2020/01/28 16:45:30 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

void		print_list(t_select *slt_struct)
{
	int	fd;

	fd = slt_struct->fd;
	print_termcap(TC_CLEAR, 1);
	slt_struct->arg_list = slt_struct->head;
	while (slt_struct->arg_list)
	{
		if (slt_struct->current == slt_struct->arg_list->id)
			print_str(slt_struct->arg_list->content, TCA_UNDERLINED, fd);
		else
			ft_putstr_fd(slt_struct->arg_list->content, fd);
		if (slt_struct->arg_list->next)
			ft_putchar_fd(' ', slt_struct->fd);
		slt_struct->arg_list = slt_struct->arg_list->next;
	}
	list_set_current_pos(slt_struct);
}

static int	print_char(int c)
{
	if (!c)
		return (ERROR);
	ft_putchar(c);
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

void	print_str(char *str, char *type, int fd)
{
	ft_putstr_fd(type, fd);
	ft_putstr_fd(str, fd);
	ft_putstr_fd(TCA_OFF, fd);
}
