/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 13:35:22 by mrandou           #+#    #+#             */
/*   Updated: 2020/01/29 13:37:48 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

int	ft_select(t_select *slt_struct)
{
	struct termios	backup;
	int				key;

	if (init_termcap())
		return (ER_NOTERM);
	if ((slt_struct->fd = init_set_attribute(&backup)) == ERROR)
		return (ER_INIT);
	while (42)
	{
		print_list(slt_struct);
		if ((key = line_read(slt_struct)) == FAILURE)
		{
			if (init_reset_attribute(backup, slt_struct->fd))
				return (ER_RESET);
			return (ER_READ);
		}
		if ((key = exec_main(slt_struct, key)) != SUCCESS)
		{
			if (init_reset_attribute(backup, slt_struct->fd))
				return (ER_RESET);
			return (key);
		}
	}
	if (init_reset_attribute(backup, slt_struct->fd))
		return (ER_RESET);
	return (FAILURE);
}

static void	put_selection(t_select *slt_struct)
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
}

int main(int argc, char **argv)
{
	struct s_select	slt_struct;
	int return_value;

	return_value = 0;
	if (argc < 2)
		return (SUCCESS);
	if (list_create(&slt_struct, argv))
		return (check_error(ER_LIST));
	return_value = ft_select(&slt_struct);
	if (return_value == RETURN)
	{
		put_selection(&slt_struct);
		return (SUCCESS);
	}
	return (check_error(return_value));
}
