/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 13:35:22 by mrandou           #+#    #+#             */
/*   Updated: 2020/01/23 18:40:02 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_select.h"

int	ft_select(char **arg_list)
{
	(void)arg_list;
	struct termios backup;
	if (init_set_attribute(&backup))
		return (FAILURE);
	while (42)
	{
		//READ
	}
	if (init_reset_attribute(backup))
		return (FAILURE);
	return (SUCCESS);
}

int main(int argc, char **argv)
{
	if (argc < 2)
		return (SUCCESS);
	return (ft_select(argv));
}
