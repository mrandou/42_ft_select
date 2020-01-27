/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 13:35:22 by mrandou           #+#    #+#             */
/*   Updated: 2020/01/27 17:45:55 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

int	ft_select(char **arg_list)
{
	struct termios	backup;
	int 			fd;
	int				error;

	if ((fd = init_set_attribute(&backup)) == ERROR)
		return (ER_INIT);
	while (42)
	{
		print_list(arg_list, fd);
		if ((error = line_edition_read(fd)))
		{
			if (init_reset_attribute(backup, fd))
				return (ER_RESET);
			return (error);
		}
	}
	if (init_reset_attribute(backup, fd))
		return (ER_RESET);
	return (SUCCESS);
}

int main(int argc, char **argv)
{
	int return_value;

	return_value = 0;
	if (argc < 2)
		return (SUCCESS);
	return_value = ft_select(argv);
	return (check_error(return_value));
}
