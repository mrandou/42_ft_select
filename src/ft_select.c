/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 13:35:22 by mrandou           #+#    #+#             */
/*   Updated: 2020/02/07 16:47:56 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

int	ft_select(t_select *slt_struct)
{
	int				key;

	get_struct(slt_struct);
	if (init_termcap())
		exit_shutdown(ER_NOTERM);
	if ((init_set_attribute(slt_struct)) == ERROR)
		exit_shutdown(ER_INIT);
	while (42)
	{
		print_list(slt_struct);
		if ((key = line_read(slt_struct)) == FAILURE)
			exit_shutdown(ER_READ);
		if ((key = exec_main(slt_struct, key)) != SUCCESS)
		{
			if (exit_reset_attribute(slt_struct))
				return (ER_RESET);
			return (key);
		}
	}
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

int main(int argc, char **argv)
{
	struct s_select	slt_struct;
	int return_value;

	return_value = 0;
	signal_init();
	if (argc < 2)
		return (SUCCESS);
	if (list_create(&slt_struct, argv))
		return (exit_check_error(ER_LIST));
	return_value = ft_select(&slt_struct);
	// debug_print_struct(&slt_struct);
	if (return_value == RETURN)
	{
		put_selection(&slt_struct);
		list_free(slt_struct.arg_list);
		return (SUCCESS);
	}
	list_free(slt_struct.arg_list);
	return (exit_check_error(return_value));
}
