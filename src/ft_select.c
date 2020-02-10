/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 13:35:22 by mrandou           #+#    #+#             */
/*   Updated: 2020/02/10 17:58:50 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

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
		display_list(slt_struct);
		if ((key = key_read(slt_struct)) == FAILURE)
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

int	main(int argc, char **argv)
{
	struct s_select	slt_struct;
	int				return_value;

	return_value = 0;
	signal_init();
	if (argc < 2)
		return (SUCCESS);
	if (list_create(&slt_struct, argv))
		return (exit_check_error(ER_LIST));
	return_value = ft_select(&slt_struct);
	if (return_value == RETURN)
	{
		display_selection(&slt_struct);
		exit_list_free(slt_struct.arg_list);
		return (SUCCESS);
	}
	exit_list_free(slt_struct.arg_list);
	return (exit_check_error(return_value));
}
