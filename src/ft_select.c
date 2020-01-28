/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 13:35:22 by mrandou           #+#    #+#             */
/*   Updated: 2020/01/28 14:57:40 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

int	ft_select(t_select *slt_struct)
{
	struct termios	backup;
	int				error;

	if (init_termcap())
		return (ER_NOTERM);
	if ((slt_struct->fd = init_set_attribute(&backup)) == ERROR)
		return (ER_INIT);
	while (42)
	{
		print_list(slt_struct);
		if ((error = line_edition_read(slt_struct)))
		{
			if (init_reset_attribute(backup, slt_struct->fd))
				return (ER_RESET);
			return (error);
		}
	}
	if (init_reset_attribute(backup, slt_struct->fd))
		return (ER_RESET);
	return (SUCCESS);
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
	return (check_error(return_value));
}
